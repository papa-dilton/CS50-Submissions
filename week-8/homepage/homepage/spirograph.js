document.documentElement.style.setProperty('--scrollbar-width', (window.innerWidth - document.documentElement.clientWidth) + "px");

var r1;
var r2;

var a1 = 0;
var a2 = 0;

var prevX;
var prevY;

const timer = window.setInterval(setup, 15000);


function setup() {
    createCanvas(document.documentElement.clientWidth, document.querySelector('.spiro').clientHeight).parent(document.querySelector('.spiro'));
    angleMode(DEGREES);
    background(28, 28, 28);
    stroke(255);

    r1 = random(100, 200)
    r2 = random(100, 200)

    a1step = random(0.1, 5)
    a2step = random(0.1, 5)

    console.log("a1step=" + a1step + "\na2step=" + a2step)
}

window.addEventListener('resize', function() {
    resizeCanvas(document.documentElement.clientWidth, document.querySelector('.spiro').clientHeight);
    setup();
})

function draw() {
    translate(width / 2, height / 2);
    for (i = 0; i < 5; i++) {

        var x1 = cos(a1) * r1
        var y1 = sin(a1) * r1

        var x2 = x1 + cos(a2) * r2
        var y2 = y1 + sin(a2) * r2


        line(prevX, prevY, x2, y2);

        prevX = x2;
        prevY = y2;

        a1 += a1step;
        a2 += a2step;

    }

}

//concept and math derived from Colorful Coding; https://www.youtube.com/watch?v=bqRvLR3PLf0