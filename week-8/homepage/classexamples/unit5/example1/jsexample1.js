const welcomeEl = document.getElementById('welcome');
const inputBoxEl = document.getElementById('nametxt');

function greet(name) {
    if (inputBoxEl.value != undefined && inputBoxEl.value != "") {
        welcomeEl.innerHTML = 'Hello, ' + name + '!';
    } else {
        welcomeEl.innerHTML = 'Hello, there!'
    }
}



function resetPage() {
    document.getElementById('pets').src = 'puppycat.jpg'
    welcomeEl.innerHTML = '&nbsp'
    inputBoxEl.value = ''
    document.getElementById('num1').value = ''
    document.getElementById('num2').value = ''
}

function calc(op) {
    const num1 = parseInt(document.querySelector('#num1').value);
    const num2 = parseInt(document.querySelector('#num2').value);
    var ansEl = document.querySelector('#ans1');
    switch (op) {
        case "+":
            ansEl.innerHTML = num1 + num2;
            break;
        case "-":
            ansEl.innerHTML = num1 - num2;
            break;
        case "/":
            ansEl.innerHTML = num1 / num2;
            break;
        case "%":
            ansEl.innerHTML = num1 % num2;
            break;
        case "*":
            ansEl.innerHTML = num1 * num2;
    }
}