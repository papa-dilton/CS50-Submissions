//vars for ball
let x = 0;
let y = 0;
let xStep = 3;
let yStep = 3;
let ballSize = 20;

//vars for player
let player1x = 50;
let player2x = 0;
let playerSpeed = 3;
let player1score = 0;
let player2score = 0;

//vars for field
let scoring = true;
let isAIControlled = true;
//lower is harder, 0.4 is reccomended -->
let aiDifficulty = 0.4;
let wrongCount = 0;

function preload() {
  blackFont = loadFont("assets/Black.ttf");
  //boldFont = loadFont('assets/ExtraBold.ttf');
  soundFormats("ogg", "wav");
  wallSound = loadSound("assets/wall");
  hitSound = loadSound("assets/hit");
  scoreSound = loadSound("assets/score");
}

function setup() {
  createCanvas(600, 400).parent(document.querySelector("#pong-canvas"));
  fill(255, 255, 255);
  noStroke();
  x = width / 2;
  y = height / 2;
  rectMode(CORNER);
  player2x = width - 50;
  player1y = height / 2 - 50;
  player2y = height / 2 - 50;
  textFont(blackFont);
  textSize(48);
  noLoop();
  setTimeout(loop, 1000);
}

function draw() {
  background(28, 28, 28);
  if (!isDesktopSize) noLoop();

  //move player rectangles

  if (keyIsDown(83) && player1y + 100 <= height) {
    player1y += playerSpeed;
  } else if (keyIsDown(87) && player1y >= 0) {
    player1y -= playerSpeed;
  }

  //player 2 is AI controlled
  if (isAIControlled) {
    if (wrongCount == 0) {
      var rand = random(1);
      if (rand <= aiDifficulty) {
        wrongCount = -1 * Math.floor(random(20));
      } else {
        wrongCount = Math.floor(random(30));
      }
    }
    if (wrongCount > 0) {
      if (y > player2y + 50 && player2y + 100 <= height) {
        player2y += playerSpeed;
      } else if (y < player2y + 50 && player2y >= 0) {
        player2y -= playerSpeed;
      }
      wrongCount--;
    } else {
      if (y > player2y + 50 && player2y >= 0) {
        player2y -= playerSpeed;
      } else if (y < player2y + 50 && player2y + 100 <= height) {
        player2y += playerSpeed;
      }
      wrongCount++;
    }
  } else {
    //player 2 is a human
    if (keyIsDown(DOWN_ARROW) && player2y + 100 <= height) {
      player2y += playerSpeed;
    } else if (keyIsDown(UP_ARROW) && player2y >= 0) {
      player2y -= playerSpeed;
    }
  }

  //move ball
  x += xStep;
  y += yStep;

  //ball collides with walls
  if ((x + ballSize / 2 >= width || x - ballSize / 2 <= 0) && !scoring) {
    xStep *= -1;
  }
  if (y + ballSize / 2 >= height || y - ballSize / 2 <= 0) {
    yStep *= -1;
    if (y <= 0) {
      y += ballSize / 2;
    } else if (y >= height) {
      y -= ballSize / 2;
    }
    wallSound.play();
  }

  //check for collisions with players
  if (
    y >= player1y - ballSize / 2 &&
    y <= player1y + ballSize / 2 + 100 &&
    x <= 10 + player1x + ballSize / 2 &&
    x >= player1x - ballSize / 2
  ) {
    /*if (y <= player1y || y >= player1y + 100) {
      yStep *= -1;
    } else {
      xStep *= -1;
    }*/

    if (
      x >= player1x &&
      x <= player1x + 10
    ) {
      if (y<=player1y) {
        yStep = -1*Math.abs(yStep);
      } else if (y>=player1y+100) {
        yStep = Math.abs(yStep);
      }

    } else if (
      y >= player1y &&
      y <= player1y + 100
    ) {
      if (x<= player1x) {
        xStep = -1*Math.abs(xStep);
      } else {
        xStep = Math.abs(xStep);
      }
    } else if (dist(x, y, player1x, player1y) <= ballSize/2 || dist(x, y, player1x+10, player1y) <= ballSize/2 || dist(x, y, player1x, player1y+100) <= ballSize/2 || dist(x, y, player1x+10, player1y+100) <= ballSize/2) {
      xStep *= -1;
      yStep *= -1;
    }
    hitSound.play();
  } else if (
    y >= player2y - ballSize / 2 &&
    y <= player2y + ballSize / 2 + 100 &&
    x <= 10 + player2x + ballSize / 2 &&
    x >= player2x - ballSize / 2
  ) {
    if (
      x >= player2x &&
      x <= player2x + 10
    ) {
      if (y<=player2y) {
        yStep = -1*Math.abs(yStep);
      } else if (y>=player2y+100) {
        yStep = Math.abs(yStep);
      }

    } else if (
      y >= player2y &&
      y <= player2y + 100
    ) {
      if (x<= player2x) {
        xStep = -1*Math.abs(xStep);
      } else {
        xStep = Math.abs(xStep);
      }
    } else if (dist(x, y, player2x, player2y) <= ballSize/2 || dist(x, y, player2x+10, player2y) <= ballSize/2 || dist(x, y, player2x, player2y+100) <= ballSize/2 || dist(x, y, player2x+10, player2y+100) <= ballSize/2) {
      xStep *= -1;
      yStep *= -1;
    }
    hitSound.play();
  }
  //draw player rectanges
  rect(player1x, player1y, 10, 100);
  rect(player2x, player2y, 10, 100);

  //draw scores
  if (scoring) {
    text(player1score, width / 2 - 50, 50);
    text(player2score, width / 2 + 50, 50);
  }

  //Draw center line
  for (i = 0; i < height / 8; i++) {
    rect(width / 2 + 20, i * 8, 4, 4);
  }

  //score
  if (scoring) {
    if (x - ballSize / 2 <= 1) {
      hitWall();
      player2score++;
      xStep = Math.abs(xStep);
    } else if (x + ballSize / 2 >= width) {
      hitWall();
      player1score++;
      xStep = -1 * Math.abs(xStep);
    }
  }

  //draw the ball
  circle(x, y, ballSize);
}

function hitWall() {
  fill(255, 0, 0);
  noLoop();
  scoreSound.play();
  yStep = Math.abs(yStep);
  setTimeout(function () {
    setup();
    loop();
  }, 1500);
}

function toggleAI() {
  if (isAIControlled) {
    isAIControlled = false;
    setup();
    player1score = 0;
    player2score = 0;
  } else {
    isAIControlled = true;
    setup();
    player1score = 0;
    player2score = 0;
  }
}

function resetGame() {
  setup();
  player1score = 0;
  player2score = 0;
}

//triggered using inline js
function changeAILevel(selected) {
  aiDifficulty = (10 - selected) / 10;
  console.log(`Difficulty changed to ${(10 - selected) / 10}`);
}

//make sure window is still sized
window.onresize = function () {
  if(window.innerWidth < 650) {
     isDesktopSize = false;
     noLoop();
  } else {
    isDesktopSize = true;
    setup();
  }
}
