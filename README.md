# Overview
Hello! I'm an MDes student at UC Berkeley, and this is my design journal for "DESINV 202: Technology Design Foundations." I will keep track of my progress per week below:

[Week 1](#week-1)

## Week 1
*(9/2 - 9/8)*
### 9/2
Tuesday, September 2nd was the day that we received our electronic kits. I was so excited to get my hardware because I love tinkering around with mini electronics, kind of makes me feel like a baby mechanic.

<img width="300" alt="" src="/assets/sept2-8/TDF-electronic-kit.JPEG">

*Looks like a little lunch box!* 

We learned how electricity works, then we received a high-level overview of some electronic components such as transformers, capacitors, and resistors. We also received instructions for powering up an Arduino and compiling a basic sketch, [HelloWorld.ino](/scripts/HelloWorld.ino).

We then received our first electronics challenge:
> Write a program to flash the onboard LED while printing Hello World to serial.

I started by taking the code from the `loop()` function in `HelloWorld.ino` and copying it into [Blink.ino](/scripts/Blink.ino), which was also pre-written for us. When I ran the sketch, the light blinked but "Hello, World!" did not print. I realized that I also needed to copy `Serial.begin(9600);` into `setup()` in order to monitor the serial data transmission feed. My first woopsie!

<img width="300" alt="" src="/assets/sept2-8/blink-hello.gif">

*GIF of light blinking and "Hello, World" printing*

[Full video of light blinking and "Hello, World" printing](/assets/sept2-8/blink-hello.MP4)

Lots to think about leaving class, kit in hand. How did I plan to address the next big challenge:

> Make “something interesting” happen with: 1 LEDs + 1 LDR, or 2 or more LEDs.

I'd need to sleep on it.

----------

### 9/4
In our fab-shop class of the week, we received our first fabrication assignment:
> Create a ring that describes a part of your personality or a cause you believe in.

I started sketching some ideas out. The term "protest ring" was brought up in class, and I believe embracing my queerness is a form of protest (as well as a significant part of my personality), so I took my swirling ideas to paper and started drawing.

<img width="300" alt="" src="/assets/sept2-8/laser-cut-ring-sketches.JPEG">

*I'm still working on the drawing skill of art!*

<img width="300" alt="" src="/assets/sept2-8/scorpious-constellation.jpg">

*Image Scorpius constellation sourced from [space.com](https://www.space.com/16947-scorpius-constellation.html)*

At first, I drew two female symbols side-by-side, but it felt a bit on the nose and uninspired, so I asked myself what a more subtle way to convey gayness could be; in other words, "IYKYK" vibes. I landed on astrology: asking for your sign is the first page in the classic lesbian playbook. Luckily for me, my sun and moon signs are both Scorpio, so I had the idea of creating a double-ring setup with an engraving of the Scorpio constellation bridging between the sun and the moon. This felt like a more subtle way to express my queer identity while also capturing some of the qualities of a Scorpio that I resonate with: somewhat dark and mysterious, but fiercely passionate and loyal. Time to learn how to bring these sketches to life through Illustrator.

### 9/8
After a busy weekend, I was ready to experiment with Arduino components. I followed the [Arduino Tutorial](https://github.com/loopstick/ArduinoTutorial) guide to wire up an external LED to the breadboard. When I tried to run the same `BlinkHello.ino` sketch, the LED didn't turn on. Another oopsie! Can't forget to ground. I plugged in the grounding wire to complete the circuit, and ouila! Let there be light!

<img width="300" alt="" src="/assets/sept2-8/first-light.JPEG">

*First external light on Arduino*

Next, I tried setting up the light dependent resistor (LDR).

<img width="300" alt="" src="/assets/sept2-8/ldr-light.JPEG">

*LDR light wiring*

I followed the Arduino guide and used code from [03a_LDR_LightSensor.ino](https://github.com/loopstick/ArduinoTutorial/blob/master/examples/03_LDR_LightSensor/03a_LDR_LightSensor/03a_LDR_LightSensor.ino) to create a new sketch [LightLDR.ino](/scripts/LightLDR.ino). Since I didn't know the value range that the LDR could output, my first iteration of the sketch was to use a constant and set it to zero so that the light would always be on:
`const int ldrToggleValue = 0`

Then I ran the sketch and tested hovering my hand over the LDR to see how the values would change.

<img width="300" alt="" src="/assets/sept2-8/ldr-light-readout-1.gif">

*LDR hand hover*

[Full video of LDR hand hover](/assets/sept2-8/ldr-light-readout-1.MP4)

The LDR readout dipped below 200 whenever my hand hovered close, so I set `ldrToggleValue` to `200`. I also wanted it to have a faster response time (in case I moved my hand over it quickly), so I reduced the delay time to `20` milliseconds.

<img width="300" alt="" src="/assets/sept2-8/ldr-light-readout-2.gif">

*LDR hand hover take 2*

[Full video of LDR hand hover take 2](/assets/sept2-8/ldr-light-readout-2.MP4)


Now, I wanted to try incorporating a second LED into my existing setup. I set up the red LED in the same way that I set up the original blue LED, and I modified my sketch to toggle on and off the LEDs with a toggle in the LDR (see [Matrix.ino](/scripts/Matrix.ino)). I could still get the blue LED to toggle on and off, but the red LED did not turn on. I troubleshooted by swapping the int values assigned at the beginning of the sketch, no luck. I tried swapping the actual LED positions on the breadboard, now the red LED did turn on, and when I hovered, the blue LED turned on. Huh, maybe I hadn't pushed the red LED in enough the first time. Swapped them back, and sure enough, it was working as expected!

<img width="300" alt="" src="/assets/sept2-8/red-blue-light.JPEG">

*Red and blue LEDs with LDR*

<img width="300" alt="" src="/assets/sept2-8/take-the-red-pill.gif">

*Take the red pill!*

[Full video of red LED blue LED toggle](/assets/sept2-8/take-the-red-pill.MP4)

----------

This round of Arduino experimentation was fun! Felt the (metaphorical) sparks of creativity flowing and excited to try more things out.
