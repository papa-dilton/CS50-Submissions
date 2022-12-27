/**JavaScript fucntions for quiz  */
var scoreArray = [0, 0, 0, 0, 0, 0];
var answerArray = ['0', 'a', 'c', 'd', 'b', 'a'];
/*
//function for making randon text and background colors
function changeColors() {
    //MAKE RANDOM TEXT COLOR
    //generate random numbers for how much red, green, blue to use
    //min is 0, max is 255
    var red = Math.floor(156 + Math.random() * 100); //possible values - 156 through 255
    var blue = Math.floor(156 + Math.random() * 100); //possible values - 156 through 255
    var green = Math.floor(156 + Math.random() * 100); //possible values - 156 through 255

    //converts numbers to hex (base 16), as text
    var r = red.toString(16);
    var g = green.toString(16);
    var b = blue.toString(16);

    //add 0 in front of any value that is a 1 digit number
    if (red.length == 1) r = '0' + r; //(ex. 9 becomes 09)
    if (green.length == 1) g = '0' + g;
    if (blue.length == 1) b = '0' + b;

    document.body.style.color = "#" + r + g + b;

    //MAKE RANDOM BACKGROUND COLOR - similar to process for text
    var red2 = Math.floor(Math.random() * 101); //possible values - 0 through 100
    var blue2 = Math.floor(Math.random() * 101); //possible values - 0 through 100
    var green2 = Math.floor(Math.random() * 101); //possible values - 0 through 100

    var r2 = red2.toString(16);
    var g2 = green2.toString(16);
    var b2 = blue2.toString(16);

    if (red.length == 1) r2 = '0' + r2;
    if (green.length == 1) g2 = '0' + g2;
    if (blue.length == 1) b2 = '0' + b2;

    document.body.style.backgroundColor = "#" + r2 + g2 + b2;



}
*/


//calculate and return score
function getScore() {
    var total = 0;
    scoreArray.forEach(i => {total += i})
    return total;
}

//display the score with user's name
function scoreIt() {
    var name = document.getElementById("namebox").value;
    var result = document.getElementById("results");
    result.innerHTML = name + ", your score is: " + getScore() + ".";
    alert(name + ', your score is ' + getScore() + '/5')

    /*const bodyEl = document.querySelector('input');
    bodyEl.classList.add('.but-rotate');*/
}

//function to tally specific questions as they are answered



function tally(q, a) {
    if (answerArray[q] == a) {
        scoreArray[q] = 1;
    } else {
        scoreArray[q] = 0;
    }

}

//function to clear out the form
function clearForm() {

    scoreArray.forEach(i => {
        scoreArray[i] = 0
    })

    document.getElementById("welcome").value = "";
    document.getElementById("namebox").value = "";
    document.getElementById("results").value = "";

    var ele = document.getElementsByName("q1");
    for (var i = 0; i < ele.length; i++)
        ele[i].checked = false;

    ele = document.getElementsByName("q2");
    for (var i = 0; i < ele.length; i++)
        ele[i].checked = false;

    ele = document.getElementsByName("q3");
    for (var i = 0; i < ele.length; i++)
        ele[i].checked = false;

    ele = document.getElementsByName("q4");
    for (var i = 0; i < ele.length; i++)
        ele[i].checked = false;

    ele = document.getElementsByName("q5");
    for (var i = 0; i < ele.length; i++)
        ele[i].checked = false;

}

function greet() {
    document.querySelector('#welcome').innerHTML = "Hello, " + document.querySelector('#namebox').value;
}