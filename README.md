# Overview
Hello! I'm an MDes student at UC Berkeley, and this is my design journal for "DESINV 202: Technology Design Foundations." I will keep track of my progress per week below:

*No journal entries for Week 1*  
[Week 2](#week-2)  
[Week 3](#week-3)  

## Week 2
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

*Image Scorpius constellation sourced from [Chandra X-ray Observatory](https://www.chandra.harvard.edu/graphics/constellations/scorpius.jpg)*

At first, I drew two female symbols side-by-side, but it felt a bit on the nose and uninspired, so I asked myself what a more subtle way to convey gayness could be; in other words, "IYKYK" vibes. I landed on astrology: asking for your sign is the first page in the classic lesbian playbook. Luckily for me, my sun and moon signs are both Scorpio, so I had the idea of creating a double-ring setup with an engraving of the Scorpio constellation bridging between the sun and the moon. This felt like a more subtle way to express my queer identity while also capturing some of the qualities of a Scorpio that I resonate with: somewhat dark and mysterious, but fiercely passionate and loyal. Time to learn how to bring these sketches to life through Illustrator.

----------

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

<img width="300" alt="" src="/assets/sept2-8/red-blue-schematic.png">

*Schematic of Matrix board, generated with [circuit-diagram.org](https://www.circuit-diagram.org/editor/)*

This round of Arduino experimentation was fun! Felt the (metaphorical) sparks of creativity flowing and excited to try more things out.

----------

## Week 3
*(9/9 - 9/15)*

### 9/9

I started designing my ring idea in Illustrator. Before I made any of the ring shapes, I thought about how I wanted the rings to sit on my fingers. Because I want to add prongs to represent the sun rays coming out of the sun, I decided to make the sun half of the ring fit on my pinky finger; that way, the prongs don't jut into my other fingers in the resting position. That means that the moon part of the ring needs to fit on my ring finger. I took loose measurements for both around the thickest part of the fingers, rounding up to the nearest tenth millimeter:

Pinkie finger: 5.3 mm => 0.209 cm
Ring finger: 5.9 mm => 0.233 inches

<img width="300" alt="" src="/assets/sept9-15/measuring-pinkie.JPEG">

*the wire is all I could find  ¯\\_(ツ)_/¯*

<img width="300" alt="" src="/assets/sept9-15/measuring-string.JPEG">

Turns out, this is not a great way to measure diameter. Since I was in the Jacobs Maker Space, I was fortunate to be able to ask Cody for his expertise. He advised me to use a caliper. I took an external measurement of my ring finger, an external measurement of my pinkie finger, and an internal measurement between the two fingers to determine the distance of separation for the rings.

<img width="300" alt="" src="/assets/sept9-15/measuring-finger-with-caliper.JPEG">

*Using the caliper*

Once I had accurate measurements of my fingers, I made my initial ring layout in Adobe Illustrator.

<img width="300" alt="" src="/assets/sept9-15/initial-ring-spacing.png">

*Circle-dash-circle*

I then added the outer circles to the initial layout so the ring has volume. Because I planned to use 1/4" plywood, Cody advised me to make the thickness of the ring at least 1/4" for stability. To make the shape of the moon crescent, I offset the outer circle and used the cut tool to take out the unnecessary lines.

<img width="300" alt="" src="/assets/sept9-15/sun-moon-cut-1.png">

*First sun-moon outline attempt*

I wasn't happy with the intersection point between the sun and moon (felt too high up to me), so I tried the offset circle technique with a more elliptical shape.

<img width="300" alt="" src="/assets/sept9-15/sun-moon-cut-2.png">

*Much better!*

I free-handed the rays on the sun and cut unnecessary lines from the outline.

<img width="300" alt="" src="/assets/sept9-15/sun-moon-with-rays-1.png">

*Actually looks like a sun now*

I was ready to do my first laser-cut test with my Illustrator file to see if the ring would fit.

<img width="300" alt="" src="/assets/sept9-15/first-laser-cut.gif">

*Baby's first laser cut in Jacobs!*

[Full video of first laser cut](/assets/sept9-15/first-laser-cut.MP4)

Oh no, it doesn't fit! Guess I messed up the caliper measurement (or squeezed it too tight around my finger). Alas, I ran out of time for the day to try again, so I'd have to try again later.

<img width="300" alt="" src="/assets/sept9-15/doesnt-fit.JPEG">

*Woops!*

----------

### 9/10

I enlarged the inner circle in the sun part of the ring in Illustrator so it would fit around my pinkie. I also wanted to make the sun rays more symmetrical, so I copied the top sun ray and duplicated it to replace the other rays along the ring. I also reduced the outline thickness to 0.0001 to work with the laser cutter, which is why the lines are much thinner now.

<img width="300" alt="" src="/assets/sept9-15/sun-moon-with-rays-2.png">

*Looks more professional now*

I ran the design through the laser cutter again, and this time the ring fits!

<img width="300" alt="" src="/assets/sept9-15/it-fits.JPEG">

*Fits like a glove*

Having confirmed my ring fit, I was ready to make the engraving of the Scorpio constellation on the ring. I used the image of Scorpius constellation from earlier and pasted it into my Illustrator canvas. I then extracted the trace from the original image, increased the contrast, then placed it on top of my ring outline.

<img width="300" alt="" src="/assets/sept9-15/scorpius-image-trace.png">

*Double Scorpio like me*

After placement, I traced the Scorpius image using red circles to cut out stars and blue lines to engrave the lines connecting the stars.

<img width="300" alt="" src="/assets/sept9-15/scorpio-constellation-on-ring.png">

*Ready for printing!*

I ran the design through the laser cutter, hoping that this would be my final iteration... Oh no, I overestimated the precision of the laser cutter with my tiny holes--it clipped right through the edges of the ring!

<img width="300" alt="" src="/assets/sept9-15/holes-clipping-outline.JPEG">

*This will give me splinters!*

I went back to my Illustrator outline and decided to take a little creative freedom. I increased the size of the holes and spread the stars out so that they would take up more space on the ring without being too close to any of the edges.

<img width="300" alt="" src="/assets/sept9-15/scorpio-constellation-on-ring-2.png">

*It's not a perfect match to the real constellation, but who will know? (Besides you)*

I cut out the new ring design, and voila! Finally, a ring that fits AND looks good!

<img width="300" alt="" src="/assets/sept9-15/scorpio-final-cut.JPEG">

*I can't wait to wear this out*

I printed a second copy of the ring *just in case* and, to put a final touch on the ring, I sanded it out to remove burn marks.

<img width="300" alt="" src="/assets/sept9-15/ring-sandpaper.JPEG">

*Scorpios and sand do go together*

Aaaaand here's how they look worn!

<img width="300" alt="" src="/assets/sept9-15/wearing-ring-1.JPEG">

<img width="300" alt="" src="/assets/sept9-15/wearing-ring-2.JPEG">

<img width="300" alt="" src="/assets/sept9-15/wearing-ring-3.JPEG">

This was such a fun project! I didn't know I had it in me to make jewelry. I'm proud to be able to show off a piece of my identity just by wearing a simple ring.

<img width="300" alt="" src="/assets/sept9-15/ring-iterations.JPEG">

*This ring has a sting (stolen from ChatGPT)*

[Link to Adobe Illustrator scorpio rings file](/assets/sept9-16/scorpio-rings.ai)

### 9/15

It was a long weekend of traveling, so now I'm back trying to figure out how to combine a button, potentiometer, and servo altogether. I had the idea to set up the button as an on/off switch, the potentiometer as an adjustable speed knob, and the servo as the output of the previous two sensors' interplay. I referenced the [Arduino Guide](https://github.com/loopstick/ArduinoTutorial?tab=readme-ov-file) to set up the button first, and then I wrote a sketch called [ButtonTest.ino](/scripts/ButtonTest.ino) based off of the Arduino guide's [07a_Button.ino](https://github.com/loopstick/ArduinoTutorial/blob/master/examples/07_Button/07a_Button/07a_Button.ino) sketch.

<img width="300" alt="" src="/assets/sept9-15/button-test.gif">

*Testing the print out for the button press*

[Full video of button press test](/assets/sept9-15/button-test.MP4)

I then tested the potentiometer by wiring it according to the Arduino Guide, then I wrote a sketch based off of [08c_Pot_AnalogInOutSerial.ino](https://github.com/loopstick/ArduinoTutorial/blob/master/examples/08_Potentiometer/08c_Pot_AnalogInOutSerial/08c_Pot_AnalogInOutSerial.ino) called [PotentiometerTest.ino](/scripts/PotentiometerTest.ino).

<img width="300" alt="" src="/assets/sept9-15/potentiometer-test.gif">

*Testing the potentiometer reading*

[Full video of button press test](/assets/sept9-15/potentiometer-test.MP4)

Finally, the trickiest looking sensor in this experimental session: the servo. I wired it up according to the Arduino Guide, then I used the [09a_Servo_Knob.ino](https://github.com/loopstick/ArduinoTutorial/blob/master/examples/09_Servo/09a_Servo_Knob/09a_Servo_Knob.ino) sketch from the guide to test the servo hooked up to the potentiometer (renamed to [ServoPotTest](/scripts/ServoPotTest.ino) in my repo).

<img width="300" alt="" src="/assets/sept9-15/servo-test.gif">

*Testing the potentiometer-servo link*

[Full video of servo test](/assets/sept9-15/servo-test.MP4)


----------