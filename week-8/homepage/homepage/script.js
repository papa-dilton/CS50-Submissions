document.documentElement.style.setProperty('--scrollbar-width', (window.innerWidth - document.documentElement.clientWidth) + "px");
//Hamburger menu for mobile devices or small windows

function burgerMenu() {
    const linkEl = document.querySelector('.nav-links');
    if (linkEl.style.display === "block") {
        linkEl.style.display = "none";
    } else {
        linkEl.style.display = "block";
    }
}

window.onresize = isMobileSize

function isMobileSize() {
    if (window.innerWidth >= 1001) {
        document.querySelector('.nav-links').style.display = 'flex';
        return false;
    } else {
        document.querySelector('.nav-links').style.display = 'none';
        document.querySelector('#burgerCheck').checked = false;
        return true;
    }
}


//To become a personalization feature

console.log(getCookie('name'));


//homepage graphic
//https://codepen.io/towc/pen/YXGYJY
var w = c.width = window.innerWidth,
    h = c.height = window.innerHeight,
    ctx = c.getContext('2d'),

    minDist = 10,
    maxDist = 30,
    initialWidth = 10,
    maxLines = 100,
    initialLines = 4,
    speed = 5,

    lines = [],
    frame = 0,
    timeSinceLast = 0,

    dirs = [
        // straight x, y velocity
        [0, 1],
        [1, 0],
        [0, -1],
        [-1, 0],
        // diagonals, 0.7 = sin(PI/4) = cos(PI/4)
        [.7, .7],
        [.7, -.7],
        [-.7, .7],
        [-.7, -.7]
    ],
    starter = { // starting parent line, just a pseudo line

        x: w / 2,
        y: h / 2,
        vx: 0,
        vy: 0,
        width: initialWidth
    };

function init() {

    lines.length = 0;

    for (var i = 0; i < initialLines; ++i)
        lines.push(new Line(starter));

    ctx.fillStyle = '#222';
    ctx.fillRect(0, 0, w, h);

    // if you want a cookie ;)
    // ctx.lineCap = 'round';
}

function getColor(x) {

    return 'hsl( hue, 80%, 50% )'.replace(
        'hue', x / w * 360 + frame
    );
}

function anim() {

    window.requestAnimationFrame(anim);

    ++frame;

    ctx.shadowBlur = 0;
    ctx.fillStyle = 'rgba(0,0,0,.02)';
    ctx.fillRect(0, 0, w, h);
    ctx.shadowBlur = .5;

    for (var i = 0; i < lines.length; ++i)

        if (lines[i].step()) { // if true it's dead

            lines.splice(i, 1);
            --i;

        }

        // spawn new

        ++timeSinceLast

    if (lines.length < maxLines && timeSinceLast > 10 && Math.random() < .5) {

        timeSinceLast = 0;

        lines.push(new Line(starter));

        // cover the middle;
        ctx.fillStyle = ctx.shadowColor = getColor(starter.x);
        ctx.beginPath();
        ctx.arc(starter.x, starter.y, initialWidth, 0, Math.PI * 2);
        ctx.fill();
    }
}

function Line(parent) {

    this.x = parent.x | 0;
    this.y = parent.y | 0;
    this.width = parent.width / 1.25;

    do {

        var dir = dirs[(Math.random() * dirs.length) | 0];
        this.vx = dir[0];
        this.vy = dir[1];

    } while (
        (this.vx === -parent.vx && this.vy === -parent.vy) || (this.vx === parent.vx && this.vy === parent.vy));

    this.vx *= speed;
    this.vy *= speed;

    this.dist = (Math.random() * (maxDist - minDist) + minDist);

}
Line.prototype.step = function() {

    var dead = false;

    var prevX = this.x,
        prevY = this.y;

    this.x += this.vx;
    this.y += this.vy;

    --this.dist;

    // kill if out of screen
    if (this.x < 0 || this.x > w || this.y < 0 || this.y > h)
        dead = true;

    // make children :D
    if (this.dist <= 0 && this.width > 1) {

        // keep yo self, sometimes
        this.dist = Math.random() * (maxDist - minDist) + minDist;

        // add 2 children
        if (lines.length < maxLines) lines.push(new Line(this));
        if (lines.length < maxLines && Math.random() < .5) lines.push(new Line(this));

        // kill the poor thing
        if (Math.random() < .2) dead = true;
    }

    ctx.strokeStyle = ctx.shadowColor = getColor(this.x);
    ctx.beginPath();
    ctx.lineWidth = this.width;
    ctx.moveTo(this.x, this.y);
    ctx.lineTo(prevX, prevY);
    ctx.stroke();

    if (dead) return true
}

init();
anim();

window.addEventListener('resize', function() {

    w = c.width = window.innerWidth;
    h = c.height = window.innerHeight;
    starter.x = w / 2;
    starter.y = h / 2;

    init();
})


//Fun easter egg. (requires use of console)

function bill(a) {
    if (a == "gates" || a == "Gates") {
        var gates = document.createElement("img");
        gates.src = "https://d.newsweek.com/en/full/1598373/bill-gates.jpg"
        document.body.insertBefore(gates, document.body.children[1]);
        openFullscreen();

        function openFullscreen() {
            if (gates.requestFullscreen) {
                gates.requestFullscreen();
            } else if (gates.webkitRequestFullscreen) { /* Safari */
                gates.webkitRequestFullscreen();
            } else if (gates.msRequestFullscreen) { /* IE11 */
                gates.msRequestFullscreen();
            }
        }
        return ("is coming...");
    } else if (a != undefined) {
        return ("Nye the science guy is " + a.toString() + "!");
    } else {
        return ("Nye the science guy!");
    }

}

//basic cookie converter to return a cookie based on the requested name

function getCookie(name) {
    name += "="
    const cookieArray = document.cookie.split('; ');
    let toReturn;
    cookieArray.forEach(value => {
        if (value.indexOf(name) == 0) toReturn = value.substring(name.length);
    })
    return toReturn;
}