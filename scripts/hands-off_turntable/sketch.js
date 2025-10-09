// modified from Dr. Sudhu's https://editor.p5js.org/loopstick/sketches/MWZxoSNoP
// and https://makeabilitylab.github.io/physcomp/communication/p5js-serial
// and JD's Nose-ifier: https://editor.p5js.org/jd/sketches/NW5vp3jEE
//
// asked ChatGPT for hand tracking code: https://chatgpt.com/share/68e3e2e9-822c-8010-9e35-796fe1ef163b

let pHtmlMsg;
let serialOptions = { baudRate: 115200  };
let serial;

let MtrSpd = 127; // neutral
let prevMtrSpd = 127;
let inc = 1;

let video;
let handPose;
let hands = [];

function preload() {
  handPose = ml5.handPose();
}

function setup() {
  createCanvas(640, 480);
  
  video = createCapture(VIDEO);
  video.size(640, 480);
  video.hide();
  
  handPose.detectStart(video, gotHands);

  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);

  // If we have previously approved ports, attempt to connect with them
  serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);

  // Add in a lil <p> element to provide messages. This is optional
  pHtmlMsg = createP("Click anywhere on this page to open the serial connection dialog");
  pHtmlMsg.style('color', 'black');
}

function gotHands(results) {
  hands = results;
}

function draw() {
  background(0);

  // Mirror the video horizontally
  push();
  translate(width, 0);
  scale(-1, 1);
  image(video, 0, 0, width, height);
  pop();

  // Draw vertical center line
  stroke(255, 0, 0);
  line(width / 2, 0, width / 2, height);

  if (hands.length > 0) {
    let hand = hands[0]; // detect just first hand

    // Support different ml5 handpose key structures
    let wrist;
    if (hand.keypoints) {
      // Modern ml5 handPose format
      wrist = hand.keypoints.find(k => k.name === "wrist" || k.part === "wrist");
    } else if (hand.annotations && hand.annotations.wrist) {
      // Older ml5 format (MediaPipe style)
      wrist = { x: hand.annotations.wrist[0][0], y: hand.annotations.wrist[0][1] };
    }

    if (wrist) {
      // Mirror x coordinate so it aligns with mirrored video
      let mirroredX = width - wrist.x;

      fill(0, 255, 0);
      noStroke();
      ellipse(mirroredX, wrist.y, 20, 20);

      // Determine direction and speed
      let centerX = width / 2;
      let direction = mirroredX > centerX ? 1 : -1;
      let speed = map(wrist.y, height, 0, 0, 128);
      MtrSpd = 127 + direction * speed;
      MtrSpd = int(constrain(MtrSpd, 0, 255));

      // Draw visual feedback
      fill(direction > 0 ? "purple" : "pink");
      noStroke();
      ellipse(mirroredX, wrist.y, 30, 30);

      textSize(16);
      fill(255);
      textAlign(CENTER);
      text(`Speed: ${abs(MtrSpd - 127)}`, mirroredX, wrist.y - 10);

      // Send to Arduino if changed significantly
      if (abs(MtrSpd - prevMtrSpd) > 2) {
        serial.writeLine(MtrSpd);
        prevMtrSpd = MtrSpd;
      }
    }
  } else {
    // No hands detected → neutral
    MtrSpd = 127;
    serial.writeLine(MtrSpd);
  }
}


// helper functions below ==========================================================================

/**
 * Callback function by serial.js when there is an error on web serial
 * 
 * @param {} eventSender 
 */
 function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  pHtmlMsg.html(error);
}

/**
 * Callback function by serial.js when web serial connection is opened
 * 
 * @param {} eventSender 
 */
function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  pHtmlMsg.html("Serial connection opened successfully");
}

/**
 * Callback function by serial.js when web serial connection is closed
 * 
 * @param {} eventSender 
 */
function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  pHtmlMsg.html("onSerialConnectionClosed");
}

/**
 * Callback function serial.js when new web serial data is received
 * 
 * @param {*} eventSender 
 * @param {String} newData new data received over serial
 */
function onSerialDataReceived(eventSender, newData) {
  console.log("onSerialDataReceived", newData);
  pHtmlMsg.html("onSerialDataReceived: " + newData);
}

/**
 * Called automatically by the browser through p5.js when mouse clicked
 */
function mouseClicked() {
  if (!serial.isOpen()) {
    serial.connectAndOpen(null, serialOptions);
  }
}