import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# export API_KEY=pk_bc742b6f32c549e5a2b89d791e5698d3

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Show portfolio of stocks
    portfolio = db.execute("SELECT * FROM portfolios WHERE user_id=?", session['user_id'])
    worth = 0.0
    for stock in portfolio:
        stock['price'] = lookup(stock['stock'])['price']
        # Get overall worth of portfolio and cash
        worth += stock['shares']*lookup(stock['stock'])['price']
    # Add any cash to worth
    cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]['cash']
    return render_template("index.html", portfolio=portfolio, worth=usd(worth), cash=usd(cash), total_worth=usd(worth+cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Show options of buying stock
    if request.method == "GET":
        return render_template("buy.html")

    # Get stock info
    try:
        shares = float(request.form.get("shares"))
    except ValueError:
        return apology("shares must be a number!", 400)
    if shares <= 0 or shares % 1 != 0:
        return apology("You musty buy a positive whole number of shares!", 400)

    symbol = request.form.get("symbol")
    stock = lookup(symbol)
    if stock == None:
        return apology("Invalid stock ticker!")
    purchaceAmt = int(shares)*stock['price']

    # Get user info
    userMoney = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]['cash']

    # Check balance and change as neccesary
    if purchaceAmt <= userMoney:
        try:
            db.execute("UPDATE users SET cash=? WHERE id=?", userMoney-purchaceAmt, session['user_id'])
            db.execute("INSERT INTO transactions (user_id, action, stock, shares, price) VALUES (?, 'buy', ?, ?, ?)", session['user_id'], symbol, shares, stock['price'])
            db.execute("INSERT INTO portfolios (user_id, stock, shares) VALUES (?, ?, ?)", session['user_id'], symbol, shares)
            flash(f"Successfuly purchaced {shares} shares of {stock['name']} for {usd(stock['price'] * shares)} at {usd(stock['price'])} each!")
        except:
             return apology("Purchace could not be completed", 500)
        return redirect("/")
    else:
        return apology("Insufficent funds!", 400)



@app.route("/history")
@login_required
def history():
    # Show history of transactions

    transactions = db.execute("SELECT action, stock, shares, price, time FROM transactions WHERE user_id=? ORDER BY time DESC", session['user_id'])
    for trans in transactions:
        trans['price'] = usd(trans['price'])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Get stock quote page
    if request.method == "GET":
        return render_template("quote.html")

    # Handle request for getting stock

    # Request API response
    stock = lookup(request.form.get("symbol"))
    if stock == None:
        return apology("Requested stock does not exist", 400)


    # Render page with stock information
    return render_template("quoted.html", company=stock['name'], ticker=stock['symbol'], price=usd(stock['price']))



@app.route("/register", methods=["GET", "POST"])
def register():
    # Render any GET requests
    if request.method == "GET":
        return render_template("register.html")

    # Store username as variable
    uname = request.form.get("username")
    # Ensure username was submitted
    if uname == "":
        return apology("Username must be submitted", 400)

    # Store password as a variable
    pwd = request.form.get("password")
    pwdConf = request.form.get("confirmation")
    # Ensure password was submitted
    if pwd == "" or pwdConf == "":
        return apology("Password fields must not be blank", 400)

    # Check for password confirmation
    if pwd != pwdConf:
        return apology("Passwords must match", 400)


    # Prevent registering an existing username
    peopleCount = db.execute("SELECT COUNT(*) FROM users WHERE username=?", uname)[0]['COUNT(*)']
    if peopleCount >= 1:
        return apology("That username is already taken", 400)

    # Hash password
    hash = generate_password_hash(pwd, method='pbkdf2:sha256', salt_length=8)

    # Insert password into DB
    try:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", uname, hash)
    except:
        return apology("Server could not make request", 503)

    # Send user to login page
    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # Render page to sell
    if request.method == "GET":
        portfolio = db.execute("SELECT * FROM portfolios WHERE user_id=?", session['user_id'])
        print(portfolio)
        return render_template("sell.html", portfolio=portfolio)

    stock = request.form.get('symbol')
    price = lookup(stock)['price']
    try:
        shares_owned = db.execute("SELECT shares FROM portfolios WHERE user_id=? AND stock=?", session['user_id'], stock)[0]['shares']
    except:
        return apology("No shares of this company owned", 400)
    shares = float(request.form.get('shares'))

    if shares <= 0:
        flash("You musty sell a positive number of shares!")
        return redirect("/sell")
    if shares < shares_owned:
        # Remove sold stocks from portfolio
        db.execute("UPDATE portfolios SET shares=? WHERE user_id=? AND stock=?", shares_owned-shares, session['user_id'], stock)
    elif shares == shares_owned:
        # Remove all stock of ticker from person
        db.execute("DELETE FROM portfolios WHERE user_id=? AND stock=?", session['user_id'], stock)

    if shares <= shares_owned:
        # Add to transaction log
        db.execute("INSERT INTO transactions (user_id, action, stock, shares, price) VALUES (?, 'sell', ?, ?, ?)", session['user_id'], stock, shares, price)
        # Add money from transaction
        userMoney = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]['cash']
        db.execute("UPDATE users SET cash=? WHERE id=?", userMoney+(price*shares), session['user_id'])

        # Return to user
        flash(f"Successfuly sold {shares} shares of {stock} at {usd(price)} each!")
        return redirect("/")
    else:
        return apology("Not enough shares owned!", 400)
@app.route("/ticker", methods=["POST"])
@login_required
def get_tickers():
    print(request.json['ticker'])
    stocks = db.execute("SELECT ticker, name FROM stocks WHERE ticker LIKE ? LIMIT 5", f"{request.json['ticker']}%")
    return stocks