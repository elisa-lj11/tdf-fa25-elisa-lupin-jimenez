# Overview
Hello! I'm an MDes student at UC Berkeley, and this is my design journal for "DESINV 202: Technology Design Foundations." I will keep track of my progress per week below:

*No journal entries for Week 1*  
[Week 2](#week-2)  
[Week 3](#week-3)  
[Week 4](#week-4)  

## Week 2
*(9/2 - 9/8)*

### 9/2 - LED Warm-Up
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

### 9/4 - Sketching My Personality Ring
In our fab-shop class of the week, we received our first fabrication assignment:
> Create a ring that describes a part of your personality or a cause you believe in.

I started sketching some ideas out. The term "protest ring" was brought up in class, and I believe embracing my queerness is a form of protest (as well as a significant part of my personality), so I took my swirling ideas to paper and started drawing.

<img width="300" alt="" src="/assets/sept2-8/laser-cut-ring-sketches.JPEG">

*I'm still working on the drawing skill of art!*

<img width="300" alt="" src="/assets/sept2-8/scorpious-constellation.jpg">

*Image Scorpius constellation sourced from [Chandra X-ray Observatory](https://www.chandra.harvard.edu/graphics/constellations/scorpius.jpg)*

At first, I drew two female symbols side-by-side, but it felt a bit on the nose and uninspired, so I asked myself what a more subtle way to convey gayness could be; in other words, "IYKYK" vibes. I landed on astrology: asking for your sign is the first page in the classic lesbian playbook. Luckily for me, my sun and moon signs are both Scorpio, so I had the idea of creating a double-ring setup with an engraving of the Scorpio constellation bridging between the sun and the moon. This felt like a more subtle way to express my queer identity while also capturing some of the qualities of a Scorpio that I resonate with: somewhat dark and mysterious, but fiercely passionate and loyal. Time to learn how to bring these sketches to life through Illustrator.

----------

### 9/8 - LED and LDR Experimentation
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

### 9/9 - Laser-Cutting the Scorpio Ring

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

### 9/10 - Refining the Scorpio Ring

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

### 9/15 - Serving Servos

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

I added back in a LED because I realized too late that the potentiometer is position based, so my original idea of using the potentiometer as a speed knob would need to be tabled. Now, the button controls the LED. I'll need to think on how to incorporate the button feedback directly into the potentiometer and servo, but for now I'll slap a llama on it as a distraction. Here's the [sketch](/scripts/LlamaDrama.ino).

<img width="300" alt="" src="/assets/sept9-15/llama-drama.gif">

*Llama drama!*

[Full video of llama spin](/assets/sept9-15/llama-drama.MP4)

<img width="300" alt="" src="/assets/sept9-15/llama-drama.JPEG">

*Llama servo breadboard layout*

----------

## Week 4
*(9/16-9/22)*

### 9/17 - Converting Laser-Cut Ring to 3D Print

I took my scorpio rings Illustrator file and exported it as a .svg file to import into Fusion.

<img width="300" alt="" src="/assets/sept16-22/initial-scorpio-rings-fusion.JPEG">

*I don't think the shading is in the right part...*

I re-exported the rings from Illustrator as a .dxf after going through and joining all the original line segments.

<img width="300" alt="" src="/assets/sept16-22/scorpio-rings-as-dxf-joined-lines.png">

*Now I'm seeing the blue shade*

I then extruded the ring body to 3 mm.

<img width="300" alt="" src="/assets/sept16-22/scorpio-ring-extruded.png">

*Chunky*

I exported the Fusion file to a .stl, which I then loaded into the Prusa GUI to prepare for printing.

<img width="300" alt="" src="/assets/sept16-22/initial-scorpio-print-whole.png">

*Whole model of scorpio rings in Prusa preview*

<img width="300" alt="" src="/assets/sept16-22/initial-scorpio-print-layers.png">

*Layered model of scorpio rings in Prusa preview*

I ran the print, which lasted 40 minutes.

<img width="300" alt="" src="/assets/sept16-22/scorpio-3d-print-in-progress.gif">

*Printing the scorpio ring*

[Full video of scorpio ring 3D printing](/assets/sept16-22/scorpio-3d-print-in-progress.MP4)

It came out pretty well! That said, I want to explore a new ring that is custom-designed for a 3D printer.

<img width="300" alt="" src="/assets/sept16-22/original-scorpio-ring-3d-print.JPEG">

*Looks pretty similar!*

[Link to scorpio-rings.stl](/assets/sept16-22/scorpio-rings-as-dxf-joined-lines.png)

----------

### 9/18 - Second Pass on 3D-Printed Ring

I started with what I thought would be a simple flower/gear idea: using the [Spur Gear Add-In](https://productdesignonline.com/fusion-360-tutorials/create-custom-3d-printable-gears-in-fusion-360/#:~:text=Accessing%20the%20Spur%20Gear%20Add,matter%20which%20one%20you%20choose.), I could make a standalone gear that would sit on top of a peg protruding from the original ring. I opened up Fusion and created a basic ring shape that would fit around my pinkie and stand 3 mm tall.

<img width="300" alt="" src="/assets/sept16-22/base-3d-ring-fusion.png">

*Ring of power*

I messed around with the fillet feature in fusion to give the ring a nice, rounded shape.

<img width="300" alt="" src="/assets/sept16-22/fillet-3d-ring.png">

*I learned it is not pronounced like the steak*

I then used the Spur Gear Add-In to make a 7-pronged gear, then I aligned it with the ring to create a peg that would fit through the gear hole. I also made a cap that would go on the end of the peg so the gear doesn't slide off, which I had planned to glue in place.

<img width="300" alt="" src="/assets/sept16-22/first-gear.png">

<img width="300" alt="" src="/assets/sept16-22/flower-gear-1.png">

<img width="300" alt="" src="/assets/sept16-22//ring-peg.png">

<img width="300" alt="" src="/assets/sept16-22/gear-cap.png">

*Can't wait to fidget with this*

I then loaded the .stl of each standalone shape onto the Prusa printer preview and ran the print.

<img width="300" alt="" src="/assets/sept16-22/flower-gear-ring-prusa.png">

<img width="300" alt="" src="/assets/sept16-22/flower-gear-ring-prusa-layers.png">

*Pretty colors*

Unfortunately, when I printed it, the details were way too small for the printer to delineate between pieces, so it came out as a total mess. The cherry on top was that the ring didn't even fit on my pinkie finger. Back to the drawing board, I suppose.

<img width="300" alt="" src="/assets/sept16-22/3d-print-flower-gear-ring-1.JPEG">

<img width="300" alt="" src="/assets/sept16-22/3d-print-flower-gear-ring-2.JPEG">

*What is this stringy mess?*

<img width="300" alt="" src="/assets/sept16-22/3d-print-ring-no-fit.JPEG">

*A ring made for ants*

I started messing around in Fusion, and as I was playing with some of the built-in 3D shape features, I had the idea to make a children's peg shape game out of a ring with a cube, a triangular prism, and a cylinder. I put the .stl of each standalone shape in the Prusa preview and printed. Sadly, I got so excited by my peg idea that I forgot I was going to run into the same issue as before with the print accuracy. Alas, perhaps the third time will be the charm.

<img width="300" alt="" src="/assets/sept16-22/peg-ring-fusion.png">

<img width="300" alt="" src="/assets/sept16-22/peg-ring-prusa-layers.png">

<img width="300" alt="" src="/assets/sept16-22/peg-ring-prusa-layers.png">

*Even more of a mess, not worth breaking apart*

I decided to go with a more simple design, using the same shape exploration I had in my last iteration but this time just leave the holes in the ring.

<img width="300" alt="" src="/assets/sept16-22/game-controller-ring.png">

*Looks like the symbols on a game controller*

I exported the model as [game-controller.stl](/assets/sept16-22/game-controller.stl) and printed it. Finally, a decent print!

<img width="300" alt="" src="/assets/sept16-22/gamer-ring.JPEG">

*Surprised the holes didn't collapse while the filament was still warm*

Here are all my attempts side-by-side.

<img width="300" alt="" src="/assets/sept16-22/all-3d-ring-print-attempts.JPEG">

----------

### 9/20 - Combining the Servo with the Ultrasonic Sensor

I hooked up the ultrasonic sensor to the breadboard using the Arduino tutorial. I left my servo plugged in but took out the potentiometer so the breadboard would be less cluttered. I installed the Ultrasonic library to my Arduino IDE by searching for the [Eric Simoes Ultrasonic library](https://github.com/ErickSimoes/Ultrasonic) within Arduino's library manager.

<img width="300" alt="" src="/assets/sept16-22/ultrasonic-library.png">

I tested that the ultrasonic sensor was taking measurements correctly by using the [UltrasonicSimple](/scripts/UltrasonicSimple.ino) sketch included with the library.

I then modified the code to make [UltrasonicServoTest.ino](/scripts/UltrasonicServoTest.ino), where I mapped the distance between an object and the ultrasonic sensor to a position on the servo.

<img width="300" alt="" src="/assets/sept16-22/servo-ultrasonic-test.gif">

*GIF of servo-ultrasonic test*

[Full video of ultrasonic sensor linked to servo movement](/assets/sept16-22/servo-ultrasonic-test.MP4)

<img width="300" alt="" src="/assets/sept16-22/servo-ultrasonic-wiring.JPEG">

*Servo-ultrasonic wiring*

Maybe I can use this for my emotive origami...

----------

### 9/22 - Exploring origami options

I had the idea to make a "blooming" flower using string attached to paper petals that could rise and fall with tension and slack in the string. The tension in the string would be created by tying the string around a ring that is fixed to the servo. Whenever the servo rotates along the z axis, the strings are pulled along with the ring rotating. I imagined making an origami-style lily since it looked like it would be easy enough to fold and have petals long enough to manipulate.

<img width="300" alt="" src="/assets/sept16-22/folding-lily-sketch.JPEG">

*Initial mechanism idea*

I practiced folding the lily using [this guide](https://www.beecreativewithseijas.com/uploads/1/2/1/3/121378154/origami-lily-print.pdf).

<img width="300" alt="" src="/assets/sept16-22/lily-origami-first-attempt.JPEG">

*A very rough start*

Maybe my paper was too small and thick. I tried again with larger, thinner diffusion paper that I found in the studio. I also looked up a [Youtube video](https://www.youtube.com/watch?v=yCn-YTti1M0) to fold so I could pay extra attention to how the folds are made.

<img width="300" alt="" src="/assets/sept16-22/lily-origami-second-attempt.JPEG">

*Not looking promising...*

I tried a third time, but it was still a failure.

<img width="300" alt="" src="/assets/sept16-22/origami-graveyard.JPEG">

*Origami graveyard*

I needed to cut my losses (quite literally) and decided to go about my moving figure in a different way.

I simplified the petals into slips of paper. As a test to see if my string method would work with the new petal, I used a boba straw, taped the string to the end of the petal, and fed the string through the straw. To my surprise, I got a curling movement instead of a "flipping" movement, which I found much more interesting than my original idea.

<img width="300" alt="" src="/assets/sept16-22/curling-leaves-with-string.gif">

*GIF of curling leaf with string*

[Full video of curling leaf with string](/assets/sept16-22/curling-leaves-with-string.MP4)

Satisfied with my new mechanism, I was ready to flesh out the programming part of the project.

----------

