# Technology Design Foundations Journal
Hello! I'm an MDes student at UC Berkeley, and this is my design journal for "DESINV 202: Technology Design Foundations." I will keep track of my progress per week below:

*No journal entries for Week 1*  
[Week 2](#week-2)  
[Week 3](#week-3)  
[Week 4](#week-4)  
[Week 5](#week-5)  
[Week 6](#week-6)  
[Week 7](#week-7)  
[Week 8](#week-8)  
[Week 9](#week-9)  
[Week 10](#week-10)  
[Week 11](#week-11)  
[Week 12](#week-12)  
[Week 13](#week-13)  
[Week 14](#week-14)  
[Week 15](#week-15)  
[Week 16](#week-16)  

## Week 2
*(9/2 - 9/8)*

### 9/2 - LED warm-Up
Tuesday, September 2nd was the day that we received our electronic kits. I was so excited to get my hardware because I love tinkering around with mini electronics, kind of makes me feel like a baby mechanic.

<img width="600" alt="" src="/assets/sept2-8/TDF-electronic-kit.JPEG">

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

### 9/4 - Sketching my personality ring
In our fab-shop class of the week, we received our first fabrication assignment:
> Create a ring that describes a part of your personality or a cause you believe in.

I started sketching some ideas out. The term "protest ring" was brought up in class, and I believe embracing my queerness is a form of protest (as well as a significant part of my personality), so I took my swirling ideas to paper and started drawing.

<img width="600" alt="" src="/assets/sept2-8/laser-cut-ring-sketches.JPEG">

*I'm still working on the drawing skill of art!*

<img width="600" alt="" src="/assets/sept2-8/scorpious-constellation.jpg">

*Image Scorpius constellation sourced from [Chandra X-ray Observatory](https://www.chandra.harvard.edu/graphics/constellations/scorpius.jpg)*

At first, I drew two female symbols side-by-side, but it felt a bit on the nose and uninspired, so I asked myself what a more subtle way to convey gayness could be; in other words, "IYKYK" vibes. I landed on astrology: asking for your sign is the first page in the classic lesbian playbook. Luckily for me, my sun and moon signs are both Scorpio, so I had the idea of creating a double-ring setup with an engraving of the Scorpio constellation bridging between the sun and the moon. This felt like a more subtle way to express my queer identity while also capturing some of the qualities of a Scorpio that I resonate with: somewhat dark and mysterious, but fiercely passionate and loyal. Time to learn how to bring these sketches to life through Illustrator.

----------

### 9/8 - LED and LDR experimentation
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

<img width="600" alt="" src="/assets/sept2-8/red-blue-schematic.png">

*Schematic of Matrix board, generated with [circuit-diagram.org](https://www.circuit-diagram.org/editor/)*

This round of Arduino experimentation was fun! Felt the (metaphorical) sparks of creativity flowing and excited to try more things out.

----------

## Week 3
*(9/9 - 9/15)*

### 9/9 - Laser-cutting the scorpio ring

I started designing my ring idea in Illustrator. Before I made any of the ring shapes, I thought about how I wanted the rings to sit on my fingers. Because I want to add prongs to represent the sun rays coming out of the sun, I decided to make the sun half of the ring fit on my pinky finger; that way, the prongs don't jut into my other fingers in the resting position. That means that the moon part of the ring needs to fit on my ring finger. I took loose measurements for both around the thickest part of the fingers, rounding up to the nearest tenth millimeter:

Pinkie finger: 5.3 mm => 0.209 cm
Ring finger: 5.9 mm => 0.233 inches

<img width="300" alt="" src="/assets/sept9-15/measuring-pinkie.JPEG">

*the wire is all I could find  ¯\\_(ツ)_/¯*

<img width="300" alt="" src="/assets/sept9-15/measuring-string.JPEG">

Turns out, this is not a great way to measure diameter. Since I was in the Jacobs Maker Space, I was fortunate to be able to ask Cody for his expertise. He advised me to use a caliper. I took an external measurement of my ring finger, an external measurement of my pinkie finger, and an internal measurement between the two fingers to determine the distance of separation for the rings.

<img width="600" alt="" src="/assets/sept9-15/measuring-finger-with-caliper.JPEG">

*Using the caliper*

Once I had accurate measurements of my fingers, I made my initial ring layout in Adobe Illustrator.

<img width="600" alt="" src="/assets/sept9-15/initial-ring-spacing.png">

*Circle-dash-circle*

I then added the outer circles to the initial layout so the ring has volume. Because I planned to use 1/4" plywood, Cody advised me to make the thickness of the ring at least 1/4" for stability. To make the shape of the moon crescent, I offset the outer circle and used the cut tool to take out the unnecessary lines.

<img width="600" alt="" src="/assets/sept9-15/sun-moon-cut-1.png">

*First sun-moon outline attempt*

I wasn't happy with the intersection point between the sun and moon (felt too high up to me), so I tried the offset circle technique with a more elliptical shape.

<img width="600" alt="" src="/assets/sept9-15/sun-moon-cut-2.png">

*Much better!*

I free-handed the rays on the sun and cut unnecessary lines from the outline.

<img width="600" alt="" src="/assets/sept9-15/sun-moon-with-rays-1.png">

*Actually looks like a sun now*

I was ready to do my first laser-cut test with my Illustrator file to see if the ring would fit.

<img width="600" alt="" src="/assets/sept9-15/first-laser-cut.gif">

*Baby's first laser cut in Jacobs!*

[Full video of first laser cut](/assets/sept9-15/first-laser-cut.MP4)

Oh no, it doesn't fit! Guess I messed up the caliper measurement (or squeezed it too tight around my finger). Alas, I ran out of time for the day to try again, so I'd have to try again later.

<img width="300" alt="" src="/assets/sept9-15/doesnt-fit.JPEG">

*Woops!*

----------

### 9/10 - Refining the scorpio ring

I enlarged the inner circle in the sun part of the ring in Illustrator so it would fit around my pinkie. I also wanted to make the sun rays more symmetrical, so I copied the top sun ray and duplicated it to replace the other rays along the ring. I also reduced the outline thickness to 0.0001 to work with the laser cutter, which is why the lines are much thinner now.

<img width="600" alt="" src="/assets/sept9-15/sun-moon-with-rays-2.png">

*Looks more professional now*

I ran the design through the laser cutter again, and this time the ring fits!

<img width="300" alt="" src="/assets/sept9-15/it-fits.JPEG">

*Fits like a glove*

Having confirmed my ring fit, I was ready to make the engraving of the Scorpio constellation on the ring. I used the image of Scorpius constellation from earlier and pasted it into my Illustrator canvas. I then extracted the trace from the original image, increased the contrast, then placed it on top of my ring outline.

<img width="600" alt="" src="/assets/sept9-15/scorpius-image-trace.png">

*Double Scorpio like me*

After placement, I traced the Scorpius image using red circles to cut out stars and blue lines to engrave the lines connecting the stars.

<img width="600" alt="" src="/assets/sept9-15/scorpio-constellation-on-ring.png">

*Ready for printing!*

I ran the design through the laser cutter, hoping that this would be my final iteration... Oh no, I overestimated the precision of the laser cutter with my tiny holes--it clipped right through the edges of the ring!

<img width="300" alt="" src="/assets/sept9-15/holes-clipping-outline.JPEG">

*This will give me splinters!*

I went back to my Illustrator outline and decided to take a little creative freedom. I increased the size of the holes and spread the stars out so that they would take up more space on the ring without being too close to any of the edges.

<img width="600" alt="" src="/assets/sept9-15/scorpio-constellation-on-ring-2.png">

*It's not a perfect match to the real constellation, but who will know? (Besides you)*

I cut out the new ring design, and voila! Finally, a ring that fits AND looks good!

<img width="300" alt="" src="/assets/sept9-15/scorpio-final-cut.JPEG">

*I can't wait to wear this out*

I printed a second copy of the ring *just in case* and, to put a final touch on the ring, I sanded it out to remove burn marks.

<img width="300" alt="" src="/assets/sept9-15/ring-sandpaper.JPEG">

*Scorpions and sand do go together*

Aaaaand here's how they look worn!

<img width="600" alt="" src="/assets/sept9-15/wearing-ring-1.JPEG">

<img width="600" alt="" src="/assets/sept9-15/wearing-ring-2.JPEG">

<img width="600" alt="" src="/assets/sept9-15/wearing-ring-3.JPEG">

This was such a fun project! I didn't know I had it in me to make jewelry. I'm proud to be able to show off a piece of my identity just by wearing a simple ring.

<img width="600" alt="" src="/assets/sept9-15/ring-iterations.JPEG">

*This ring has a sting (stolen from ChatGPT)*

[Link to Adobe Illustrator scorpio rings file](/assets/sept9-16/scorpio-rings.ai)

### 9/15 - Serving servos

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

<img width="600" alt="" src="/assets/sept9-15/llama-drama.JPEG">

*Llama servo breadboard layout*

----------

## Week 4
*(9/16-9/22)*

### 9/17 - Converting laser-cut ring to 3D print

I took my scorpio rings Illustrator file and exported it as a .svg file to import into Fusion.

<img width="600" alt="" src="/assets/sept16-22/initial-scorpio-rings-fusion.JPEG">

*I don't think the shading is in the right part...*

I re-exported the rings from Illustrator as a .dxf after going through and joining all the original line segments.

<img width="600" alt="" src="/assets/sept16-22/scorpio-rings-as-dxf-joined-lines.png">

*Now I'm seeing the blue shade*

I then extruded the ring body to 3 mm.

<img width="600" alt="" src="/assets/sept16-22/scorpio-ring-extruded.png">

*Chunky*

I exported the Fusion file to a .stl, which I then loaded into the Prusa GUI to prepare for printing.

<img width="600" alt="" src="/assets/sept16-22/initial-scorpio-print-whole.png">

*Whole model of scorpio rings in Prusa preview*

<img width="600" alt="" src="/assets/sept16-22/initial-scorpio-print-layers.png">

*Layered model of scorpio rings in Prusa preview*

I ran the print, which lasted 40 minutes.

<img width="300" alt="" src="/assets/sept16-22/scorpio-3d-print-in-progress.gif">

*Printing the scorpio ring*

[Full video of scorpio ring 3D printing](/assets/sept16-22/scorpio-3d-print-in-progress.MP4)

It came out pretty well! That said, I want to explore a new ring that is custom-designed for a 3D printer.

<img width="600" alt="" src="/assets/sept16-22/original-scorpio-ring-3d-print.JPEG">

*Looks pretty similar!*

[Link to scorpio-rings.stl](/assets/sept16-22/scorpio-rings-as-dxf-joined-lines.png)

----------

### 9/18 - Second pass on 3D-printed ring

I started with what I thought would be a simple flower/gear idea: using the [Spur Gear Add-In](https://productdesignonline.com/fusion-360-tutorials/create-custom-3d-printable-gears-in-fusion-360/#:~:text=Accessing%20the%20Spur%20Gear%20Add,matter%20which%20one%20you%20choose.), I could make a standalone gear that would sit on top of a peg protruding from the original ring. I opened up Fusion and created a basic ring shape that would fit around my pinkie and stand 3 mm tall.

<img width="600" alt="" src="/assets/sept16-22/base-3d-ring-fusion.png">

*Ring of power*

I messed around with the fillet feature in fusion to give the ring a nice, rounded shape.

<img width="600" alt="" src="/assets/sept16-22/fillet-3d-ring.png">

*I learned it is not pronounced like the steak*

I then used the Spur Gear Add-In to make a 7-pronged gear, then I aligned it with the ring to create a peg that would fit through the gear hole. I also made a cap that would go on the end of the peg so the gear doesn't slide off, which I had planned to glue in place.

<img width="600" alt="" src="/assets/sept16-22/first-gear.png">

<img width="600" alt="" src="/assets/sept16-22/flower-gear-1.png">

<img width="600" alt="" src="/assets/sept16-22//ring-peg.png">

<img width="600" alt="" src="/assets/sept16-22/gear-cap.png">

*Can't wait to fidget with this*

I then loaded the .stl of each standalone shape onto the Prusa printer preview and ran the print.

<img width="600" alt="" src="/assets/sept16-22/flower-gear-ring-prusa.png">

<img width="600" alt="" src="/assets/sept16-22/flower-gear-ring-prusa-layers.png">

*Pretty colors*

Unfortunately, when I printed it, the details were way too small for the printer to delineate between pieces, so it came out as a total mess. The cherry on top was that the ring didn't even fit on my pinkie finger. Back to the drawing board, I suppose.

<img width="600" alt="" src="/assets/sept16-22/3d-print-flower-gear-ring-1.JPEG">

<img width="600" alt="" src="/assets/sept16-22/3d-print-flower-gear-ring-2.JPEG">

*What is this stringy mess?*

<img width="600" alt="" src="/assets/sept16-22/3d-print-ring-no-fit.JPEG">

*A ring made for ants*

I started messing around in Fusion, and as I was playing with some of the built-in 3D shape features, I had the idea to make a children's peg shape game out of a ring with a cube, a triangular prism, and a cylinder. I put the .stl of each standalone shape in the Prusa preview and printed. Sadly, I got so excited by my peg idea that I forgot I was going to run into the same issue as before with the print accuracy. Alas, perhaps the third time will be the charm.

<img width="600" alt="" src="/assets/sept16-22/peg-ring-fusion.png">

<img width="600" alt="" src="/assets/sept16-22/peg-ring-prusa-layers.png">

<img width="600" alt="" src="/assets/sept16-22/peg-ring-prusa-layers.png">

*Even more of a mess, not worth breaking apart*

I decided to go with a more simple design, using the same shape exploration I had in my last iteration but this time just leave the holes in the ring.

<img width="600" alt="" src="/assets/sept16-22/game-controller-ring.png">

*Looks like the symbols on a game controller*

I exported the model as [game-controller.stl](/assets/sept16-22/game-controller.stl) and printed it. Finally, a decent print!

<img width="600" alt="" src="/assets/sept16-22/gamer-ring.JPEG">

*Surprised the holes didn't collapse while the filament was still warm*

Here are all my attempts side-by-side.

<img width="600" alt="" src="/assets/sept16-22/all-3d-ring-print-attempts.JPEG">

----------

### 9/20 - Combining the servo with the ultrasonic sensor

I hooked up the ultrasonic sensor to the breadboard using the Arduino tutorial. I left my servo plugged in but took out the potentiometer so the breadboard would be less cluttered. I installed the Ultrasonic library to my Arduino IDE by searching for the [Eric Simoes Ultrasonic library](https://github.com/ErickSimoes/Ultrasonic) within Arduino's library manager.

<img width="300" alt="" src="/assets/sept16-22/ultrasonic-library.png">

I tested that the ultrasonic sensor was taking measurements correctly by using the [UltrasonicSimple](/scripts/UltrasonicSimple.ino) sketch included with the library.

I then modified the code to make [UltrasonicServoTest.ino](/scripts/UltrasonicServoTest.ino), where I mapped the distance between an object and the ultrasonic sensor to a position on the servo.

<img width="600" alt="" src="/assets/sept16-22/servo-ultrasonic-test.gif">

*GIF of servo-ultrasonic test*

[Full video of ultrasonic sensor linked to servo movement](/assets/sept16-22/servo-ultrasonic-test.MP4)

<img width="600" alt="" src="/assets/sept16-22/servo-ultrasonic-wiring.JPEG">

*Servo-ultrasonic wiring*

Maybe I can use this for my emotive origami...

----------

### 9/22 - Exploring origami options

I had the idea to make a "blooming" flower using string attached to paper petals that could rise and fall with tension and slack in the string. The tension in the string would be created by tying the string around a ring that is fixed to the servo. Whenever the servo rotates along the z axis, the strings are pulled along with the ring rotating. I imagined making an origami-style lily since it looked like it would be easy enough to fold and have petals long enough to manipulate.

<img width="600" alt="" src="/assets/sept16-22/folding-lily-sketch.JPEG">

*Initial mechanism idea*

I practiced folding the lily using [this guide](https://www.beecreativewithseijas.com/uploads/1/2/1/3/121378154/origami-lily-print.pdf).

<img width="600" alt="" src="/assets/sept16-22/lily-origami-first-attempt.JPEG">

*A very rough start*

Maybe my paper was too small and thick. I tried again with larger, thinner diffusion paper that I found in the studio. I also looked up a [Youtube video](https://www.youtube.com/watch?v=yCn-YTti1M0) to fold so I could pay extra attention to how the folds are made.

<img width="600" alt="" src="/assets/sept16-22/lily-origami-second-attempt.JPEG">

*Not looking promising...*

I tried a third time, but it was still a failure.

<img width="600" alt="" src="/assets/sept16-22/origami-graveyard.JPEG">

*Origami graveyard*

I needed to cut my losses (quite literally) and decided to go about my moving figure in a different way.

I simplified the petals into slips of paper. As a test to see if my string method would work with the new petal, I used a boba straw, taped the string to the end of the petal, and fed the string through the straw. To my surprise, I got a curling movement instead of a "flipping" movement, which I found much more interesting than my original idea.

<img width="300" alt="" src="/assets/sept16-22/curling-leaves-with-string.gif">

*GIF of curling leaf with string*

[Full video of curling leaf with string](/assets/sept16-22/curling-leaves-with-string.MP4)

Satisfied with my new mechanism, I was ready to flesh out the programming part of the project.

----------

## Week 5
*(9/23 - 9/29)*
### 9/23 - Emotive origami crunch time

I wanted to build off of my previous `UltrasonicServoTest.ino` sketch and remove the jittering and `delay()` call, so I consulted ChatGPT to help me generate a smoothing function based off the original code. ChatGPT suggested that I use an `alpha` constant to control the strength of the smoothing, and an exponential moving average function that takes a fraction of the new reading (`rawDistance`) and adds it to the remaining fraction of the old distance (`distance`) to set the new smoothed distance. Since the smoothing function is called continuously, there is no need to run the `delay()` line to make updates.

```distance = alpha * rawDistance + (1 - alpha) * distance;```

<img width="600" alt="" src="/assets/sept23-29/smooth-servo.gif">

*GIF of the servo with the new smoothing code*

[Full video of smooth servo](/assets/sept23-29/smooth-servo.MP4)

It worked like a charm! Only thing I need to be mindful of when I am placing the ultrasonic sensor within the containing box is that the readings get confused within 2 cm (I think the ultrasonic sensor stops reading accurately when the noise is bouncing off too close to its origin), so I may want to place the sensor a little deeper into the box so that users don't run into this issue.

Here is the [ShyGuy.ino](/scripts/ShyGuy.ino) sketch, which I affectionately named because I'm envisioning the paper curling like it's shy when it gets attention (i.e., a hand moving toward it).

To confirm that my idea for the project would work with the servo, I taped a dowel to the servo arm and held the boba straw with the strip of paper and string, which I taped to the end of the dowel.

<img width="300" alt="" src="/assets/sept23-29/curly-paper-servo-first-try.gif">

*GIF of the servo with the boba paper low fidelity prototype*

[Full video of curly paper servo](/assets/sept23-29/curly-paper-servo-first-try.MP4)

Feeling more confident with my rough prototype, I tried it again with two leaves and cardstock paper. I flipped the string to the top and curled the paper on the edge of scissors to give it a natural curl in the resting position. I attached the two strings to the dowel and ran the 

<img width="600" alt="" src="/assets/sept23-29/curly-paper-servo-second-try.gif">

*GIF of the second attempt with cardstock and the servo*

[Full video of curly paper servo second attempt](/assets/sept23-29/curly-paper-servo-second-try.MP4)

On to the laser cut for my flower, which is making a comeback now that I've figured out how to get it to bloom.

I made the sketch for the flower in Fusion. I started with a simple circle and put a much smaller circle inside (where the string would be fed through), then used the fit point spline tool to shape the first petal. I copied the petal to make four petals total and spaced them around the circle. I used the fillet tool to round the edges between the petal root and the edge of the circle.

<img width="600" alt="" src="/assets/sept23-29/flower-cut-fusion-1.png">

*First pass at flower design in Fusion*

I then exported the file from Fusion as [flower-cut.dxf](/assets/sept23-29/flower-cut.dxf) and imported into an Illustrator file called [flower-cut.ai](/assets/sept23-29/flower-cut.ai). I cleaned up some of the extra circles and edges, then I ran the print.

<img width="600" alt="" src="/assets/sept23-29/flower-cut-illustrator-1.png">

*Flower design imported into Illustrator and cleaned up*

<img width="600" alt="" src="/assets/sept23-29/flower-laser-cut-1.JPEG">

*First flower laser cut*

I taped a piece of string to each petal, pushed the string through the boba straw, then taped them all to a point on the dowel taped to the servo.

<img width="300" alt="" src="/assets/sept23-29/flower-cut-attached-to-servo.gif">

*The prototype is working!*

[Full video of first flower prototype](/assets/sept23-29/flower-cut-attached-to-servo.MP4)

I realized I did not want tape to be externally visible in my final prototype, so I used an exact knife to cut a couple slits into the edge of the petal so that I could tie the string around it.

<img width="300" alt="" src="/assets/sept23-29/slits-in-flower.JPEG">

*Starting to look more refined*

I went back to Fusion and added in the slits. I also cleaned up the geometry while in Fusion so I wouldn't have to do it in Illustrator, then I exported the file as [flower-cut-2.dxf](/assets/sept23-29/flower-cut-2.dxf).

<img width="600" alt="" src="/assets/sept23-29/flower-cut-fusion-2.png">

*Second pass at flower design in Fusion*

I imported this into Illustrator and ran a cut. Unfortunately, the slits were way too small, so I had to go back to Illustrator and size them up, which is contained in [flower-cut-2.ai](/assets/sept23-29/flower-cut-2.ai).

<img width="600" alt="" src="/assets/sept23-29/flower-cut-illustrator-2.png">

*Second flower design in Illustrator*

With my final flower cut design, I used a sewing needle to thread the string into the four petals.

<img width="600" alt="" src="/assets/sept23-29/sewing-flower.JPEG">

*Never thought I'd be sewing paper*

<img width="600" alt="" src="/assets/sept23-29/flower-strung-out.JPEG">

*My flower is strung out*

Now that I had all the individual parts ready, I needed to put it all together. I cut a hole into the top of the box for the straw, cut another two holes into the side of the box (one for each cylinder on the ultrasonic sensor), taped all my components underneath, and placed the boba straw, string, and flower in position. I taped the string to the dowel on the servo, and I tested it out (holding my breath).

<img width="600" alt="" src="/assets/sept23-29/components-taped-inside-box.JPEG">

*Tape is temporary, I promise*

<img width="600" alt="" src="/assets/sept23-29/flower-cut-medfi-prototype.gif">

*Medium fidelity prototype in action*

[Full video of medium fidelity flower prototype](/assets/sept23-29/flower-cut-medfi-prototype.MP4)

<img width="600" alt="" src="/assets/sept23-29/medfi-mechanism.gif">

*Underside of the medium fidelity prototype*

[Full video of medium fidelity mechanism](/assets/sept23-29/flower-cut-medfi-prototype.MP4)

Whoo, that was a late night of work! I'll leave the final touches to tomorrow.

----------

### 9/24 - Bringing Shy Guy across the finish line

It was my last day to work on Shy Guy, but I was feeling pretty good about where I left off from the day before. All that I had left was to clean up the appearance of the straw and fix the components into place (without tape).

The straw took a disproportionate amount of my headspace because my original idea--to wrap it in paper the same color as the flower--looked horrible. The edge of the paper was clearly visible, creating a seam along the length of the straw that was distracting. For some reason, my sleep-deprived brain jumped to coming up with a 3D-printed solution, so I took to Fusion once again.

I designed the straw to fit into the hole I had already cut in the box, and I added a little lip that would sit on top of the box to prevent it from wiggling.

<img width="200" alt="" src="/assets/sept23-29/3d-print-boba-straw.png">

*Over-engineered a bit*

After 30 minutes of CAD work, I learned from a design specialist that this print would actually fail because the filament would not be able to support itself when it is being shaped into something as tall and skinny as a straw. Sad face. Here's [boba-straw.stl](/assets/sept23-29/boba-straw.stl) anyway.

What else could I possibly do, other than wrap paper around the straw and 3D print? Oh right, good old-fashioned paint still exists. I brought the straw to our spray-paint fume hood corner and sprayed that straw up.

<img width="300" alt="" src="/assets/sept23-29/black-straw.JPEG">

<img width="300" alt="" src="/assets/sept23-29/white-straw.JPEG">

*Sometimes the best solutions are the most simple*

I still needed some kind of fixture to prevent the straw from wiggling so much with the servo movement, so I decided to make (yet another) laser cut ring, designed in Illustrator as [flower-ring-hold.ai](/assets/sept23-29/flower-ring-hold.ai) that I could glue to the underside of the box.

<img width="600" alt="" src="/assets/sept23-29/flower-ring-hold.png">

<img width="300" alt="" src="/assets/sept23-29/flower-ring-hold-cut.JPEG">

*Huh, wonder where I got all that practice making rings...*

To cleanly mount all the components, I used command strips for the power bank and the Arduino, which would hold them in place upside-down firmly but also make it easy to remove them without leaving any residue on the components themselves. I tried using a cut command strip for the servo, but the little thing was just too powerful, it kept tearing itself off the strip anytime it pulled on the flower. I had to pull out the hot glue gun for this small but mighty component. I also hot-glued the straw ring over the straw hole on the underside of the box. While I waited for the glue to dry, I changed the wires out on the breadboard so everything would look tidier.

<img width="600" alt="" src="/assets/sept23-29/command-strip.JPEG">

*Command strips > duct tape*

<img width="600" alt="" src="/assets/sept23-29/hot-glue-servo.JPEG">

*I put just a little dab of hot glue*

Here's the high fidelity wiring and mechanism:

<img width="600" alt="" src="/assets/sept23-29/high-fidelity-wiring.JPEG">

<img width="600" alt="" src="/assets/sept2-8/red-blue-schematic.png">

*Schematic of Shy Guy, generated with [circuit-diagram.org](https://www.circuit-diagram.org/editor/)*

<img width="600" alt="" src="/assets/sept23-29/final-mechanism.gif">

*I know I promised no tape, but the little servo pulled itself off even with the hot glue! Please forgive me...*

[Full video of high fidelity mechanism](/assets/sept23-29/final-mechanism.MP4)

And with that, Shy Guy was ready to ~see~ hide from the world!

<img width="600" alt="" src="/assets/sept23-29/shy-guy-hifi-prototype.JPEG">

<img width="600" alt="" src="/assets/sept23-29/shy-guy-hifi-prototype-2.JPEG">

<img width="600" alt="" src="/assets/sept23-29/shy-guy-hifi-prototype-3.JPEG">

<img width="600" alt="" src="/assets/sept23-29/shy-guy-hifi-prototype-4.JPEG">

*He's my baby*

See gifs below for a quick demonstration of Shy Guy in action.

<img width="600" alt="" src="/assets/sept23-29/shy-guy-#demo-1.gif">

<img width="600" alt="" src="/assets/sept23-29/shy-guy-demo-2.gif">

<img width="600" alt="" src="/assets/sept23-29/shy-guy-demo-3.gif">

[Full video of shy guy demo 1](/assets/sept23-29/shy-guy-demo-1.MP4)  
[Full video of shy guy demo 2](/assets/sept23-29/shy-guy-demo-2.MP4)  
[Full video of shy guy demo 2](/assets/sept23-29/shy-guy-demo-3.MP4)  

What a fun week! I'm glad I got to experiment with the Arduino, laser cutting, and 3D printing (even if I didn't end up printing anything) all in one project. I'm proud of what I came up with; I didn't think I could make a flower like this in just a week's time! I'm excited to do more hybrid technology development like this over the semester, and I'm especially excited to work with my brilliant cohort on more projects together.

----------

## Week 6
*(9/30 - 10/4)*

### 10/3 - Testing the DC motor

We moved into our next project, "Expressive Mechanics," where we were tasked with using a DC motor and computer vision to create an interaction between movement and an actuator. My first step in this project was to get the DC motor to run through a combination of Arduino code and [p5.js](https://p5js.org/), an online IDE that fuses coding with art. I didn't quite have an idea of what kind of project I wanted to make yet, but I wanted to get the DC motor set up at a minimum.

Following Dr. Sudhu's [H-Bridge Motor Driver guide](https://github.com/loopstick/ArduinoTutorial?tab=readme-ov-file#h-bridge-motor-driver), I needed to solder two wires to the DC motor in order to connect it to my Arduino. I started by stripping the plastic case off of one side of my jumper cables.

<img width="600" alt="" src="/assets/sept30-oct4/stripping-wire.JPEG">

*Somewhat satisfying*

I used the soldering station to attach the wires to the DC motor.

<img width="600" alt="" src="/assets/sept30-oct4/solder-dc-motor.JPEG">

*Yummy solder juice*

I used a ziptie to secure the wires to the motor (in case they snag on anything during assembly and rip out of their solder joints).

<img width="600" alt="" src="/assets/sept30-oct4/zip-tied-wires-to-motor.JPEG">

*Is this secure enough?*

I used a screwdriver to tighten the screws around the wires connected into the H-bridge.

<img width="600" alt="" src="/assets/sept30-oct4/h-bridge-screw-connection.JPEG">

*I didn't realize wires could actually be fastened to electronics with screws*

I wired everything together (Arduino, DC motor, and H-bridge) according to the schematic in the guide.

I used a screwdriver to tighten the screws around the wires connected into the H-bridge.

<img width="600" alt="" src="/assets/sept30-oct4/dc-motor-h-bridge-arduino-wiring.JPEG">

*May need to do some wire management later*

To make sure the connections were properly secured, I loaded up Dr. Sudhu's [Makeability motor sketch](/scripts/Makeability_serialIO_v4c_motor.ino)

<img width="300" alt="" src="/assets/sept30-oct4/dc-motor-test.gif">

*GIF of DC motor test*

[Full video of DC motor test](/assets/sept30-oct4/dc-motor-test.MP4)

With that, I felt good about moving to the fabrication side of my project.

----------

### 10/4 - Designing the laser-cut base

I wanted to play around with gears for my mechanic, so I had this idea to make a turntable with gears. I drew out a sketch with the basic idea.

<img width="600" alt="" src="/assets/sept30-oct4/turntable-sketch.JPEG">

*Little turntable diagram with component placement*

I also drew out the gear rotations to verify the number of gears I would need to make the turntable work.

<img width="600" alt="" src="/assets/sept30-oct4/gear-sketch.JPEG">

*More on this later*

To meet the project requirements, I needed to laser-cut the base to hold the components, so I started by sketching out the placement of the Arduino, H-bridge, DC motor, and wire holes to make measurements.

<img width="600" alt="" src="/assets/sept30-oct4/components-in-base-sketch.JPEG">

*Components laid out on paper*

I then measured the dimensions of the sketched components so I could design it in Illustrator.

<img width="600" alt="" src="/assets/sept30-oct4/components-in-base-sketch-dimensions.JPEG">

*Metric is the way*

I found a neat component box generator online called [MakerCase](https://www.makercase.com/basicBox) and used flat joints to minimize distracting edges on the box.

<img width="600" alt="" src="/assets/sept30-oct4/makercase-box-generator.png">

*Nice that people offer this for free online*

I downloaded the model as [makercase_generated_box.dxf](/assets/sept30-oct4/makercase_generated_box.dxf) and imported it into Illustrator.

<img width="600" alt="" src="/assets/sept30-oct4/makercase-imported-illustrator.png">

*Fairly simple look*

I added the dimensions of the components to the MakerCase layout using a blue color to engrave the correct placement. I designed a hole with a 2-centimeter diameter slightly offset from the vertical center of the box by creating a duplicate circle and using the anchor tools to center the two circle side-by-side since I wanted the two inside gears of my turntable to be centered on the platform.

<img width="600" alt="" src="/assets/sept30-oct4/makercase-with-layout-1.png">

*This took me 3 hours total sadly*

I brought the [makercase-with-layout.ai](/assets/sept30-oct4/makercase-with-layout.ai) file to the laser cutter to finally make my cut after spending way too much time trying to perfect the layout.

When I finished the cut, I laid all my components into the case and taped it together to see how they would sit. Oops! I accidentally put the wire hole at the bottom of the case, and the plastic cover around the Arduino wire did not have enough give to make the bend toward the hole.

<img width="600" alt="" src="/assets/sept30-oct4/makercase-layout-mistake.JPEG">

*Why did I spend 3 hours doing this*

I needed to redesign just the back board of my case to put the wire cutout in the right spot without revealing the placement text I engraved into the walls. I re-cut with [a fixed version of the back panel](/assets/sept30-oct4/makercase-with-layout-back-fixed.ai) which would put less stress on the wires.

After resolving that mistake, I could drill the holes to mount the components into the base board. I used a hand drill after tracing out the holes in the component frames with a pencil.

<img width="600" alt="" src="/assets/sept30-oct4/drill-component-holes.JPEG">

*I feel powerful*

Sadly, I hadn't sandwiched my base board properly, so when I drilled through, the wood splintered on the outward-facing part of the board. Sad times, but I must forge ahead. I found standups to place in the holes, then mounted the components into place.

<img width="600" alt="" src="/assets/sept30-oct4/base-standup-placement.JPEG">

<img width="600" alt="" src="/assets/sept30-oct4/base-standup-component-placement.JPEG">

*At least the holes lined up with the components*

That's enough sloppy designing for one day. Time to take a proper weekend break.

----------

## Week 7
*(10/5 - 10/11)*

### 10/6 - Playing around with p5.js

After playing around with Dr. Sudhu's ["happy little skies" sketch](https://openprocessing.org/sketch/2584640) on the OpenProcessing website and his [DC motor p5.js sketch](https://editor.p5js.org/loopstick/sketches/MWZxoSNoP) on the p5.js online editor, I wanted to try setting up a simple computer vision sketch for eye tracking. Sadly, I quickly discovered via ChatGPT that the computer vision model that we would use is not sensitive enough to detect eye position. I still wanted to do something that played around with a different motion than ear positions, so I decided to explore hand movement.

I started by trying to detect two hands, where each hand can determine the summed speed, but I got wonky behavior when I had two hands up, so I limited the detection to just one hand.

<img width="600" alt="" src="/assets/oct5-11/cv-hands-first-test.gif">

*GIF of hand tracking motor test*

[Full video of hand tracking motor test](/assets/oct5-11/cv-hands-first-test.MP4)

One thing I noticed with the code is that the motor doesn't start spinning until it detects a value over 25, so I would need to figure out what was going on here, but that would be a later problem.

----------
### 10/7 - Making the turntable gears

Back to the fabrication portion of my project, I designed the gears in Fusion using the [Spur Gear Add-In](https://productdesignonline.com/fusion-360-tutorials/create-custom-3d-printable-gears-in-fusion-360/#:~:text=Accessing%20the%20Spur%20Gear%20Add,matter%20which%20one%20you%20choose.) that I had wanted to use for my [laser-cut ring project from earlier](### 9/18 - Second pass on 3D-printed ring). I measured the dimensions of the square portion on the 3D-printed peg that came with my DC motor to make a cut-out in the gear that would actuate the system, and I made the gear have the diameter of the hole that I cut out so it would be flush with the peg. I also measured the diameter of the dowel.

<img width="600" alt="" src="/assets/oct5-11/measuring-square-peg.JPEG">

<img width="600" alt="" src="/assets/oct5-11/measuring-square-peg.JPEG">

<img width="600" alt="" src="/assets/oct5-11/small-spur-gears-fusion.png">

*Looking good so far*

I added two larger gears to serve as the base for the records on the turntable, being careful to make the teeth on all the gears the same size and distance apart so they would fit together neatly. I also added in holes into the gears not connected directly to the motor that would fit a dowel. I then exported the Fusion sketch as [a .dxf file](/assets/oct5-11/expressive-mechanics-gears.dxf) into Illustrator and laid out the gears to be cut neatly into a plywood piece.

<img width="600" alt="" src="/assets/oct5-11/all-spur-gears-fusion.png">

<img width="600" alt="" src="/assets/oct5-11/all-spur-gears-illustrator.png">

*Hopefully the geometry is correct...*

Unfortunately, the laser cutter unexpectedly disconnected four minutes into the job, so I was left with jagged-edged gears.

<img width="600" alt="" src="/assets/oct5-11/broken-gears.JPEG">

*We were so close!*

I still wanted to make use of the messed-up gears, though, so I tested the spinning mechanic with the motor by holding it in place.

<img width="300" alt="" src="/assets/oct5-11/testing-gear-mechanic.gif">

*GIF of gear mechanic test*

[Full video of gear mechanic test](/assets/oct5-11/testing-gear-mechanic.MP4)

Feeling more confident that my design would work, I ran the laser cut again and got a perfect gear cut this time.

<img width="600" alt="" src="/assets/oct5-11/gears-laser-cut.JPEG">

*Woohoo*

I sanded the gears to remove the burn marks, then I got to work on the base board. I realized I was pretty unhappy with the splintered wood in my original base plate, so I redesigned the [base board file](/assets/sept30-oct4/makercase-with-layout-back-fixed.ai) to incorporate the holes for the dowels.

<img width="600" alt="" src="/assets/oct5-11/new-base-board-illustrator.png">

*More respectable*

After recutting the board, I was much more happy with the results; it was well-worth the effort to re-do.

<img width="600" alt="" src="/assets/oct5-11/before-after-base.JPEG">

*What a difference*

Then, I mounted all the components into place.

<img width="600" alt="" src="/assets/oct5-11/components-fixed-to-base.JPEG">

*A little cleanup required*

I squeezed the dowels into the holes of the base board, only to realize if my gears rested directly on the base board, there would be too much friction for them to spin smoothly. As a solution, I designed some [wooden "standoffs"](/assets/oct5-11/gear-standoffs.ai) for my gears to give them some lift off of the platform.

<img width="600" alt="" src="/assets/oct5-11/gear-standoffs.JPEG">

*It's a tight fit*

Unfortunately, I didn't account for slightly discrepancies in measurements, so the holes in my baseboard were slightly too small for the dowels. I first used a hand drill to open up the holes in the gears, then I attached the dowel as an attachment to the hand drill to sand down the dowels by holding the sandpaper around the spinning dowel.

<img width="600" alt="" src="/assets/oct5-11/opening-up-dowel-holes.JPEG">

*Maybe laser-cutting again would have been faster...*

Once the dowels could squeeze into the platform holes, I cut the dowels to be just tall enough to give the gears clearance from the platform and the 3D-printed motor peg.

<img width="600" alt="" src="/assets/oct5-11/placing-dowels-in-base.JPEG">

*It's really coming together now*

I placed the gears onto the dowels and tested out the motor, holding the base board and motor in place.

<img width="600" alt="" src="/assets/oct5-11/gears-spinning-first-time.gif">

*IT'S WORKING*

[Full video of gears mechanically spinning for the first time](/assets/oct5-11/gears-spinning-first-time.MP4)

An important side-note: I realized I had messed up my gear math. I thought my bigger gears would rotate in the same direction, but it turns out I messed up in my original sketch, so now they rotate toward and away from each other. Aw well, iT'S a FeAtUrE, nOt A bUg.

Confident with my rig, I hot-glued the dowels in place. I used wood blocks to lift the motor up along the side wall so that just the square peg on the 3D-printed motor mount would stick out of the hole. I drilled the 3D-printed motor case to the wood block, then I wood glued the block to the side wall of the component case. It was difficult to get the motor mount to be perfectly level with the box, so I had to hope it would stick in the right place.
  
<img width="600" alt="" src="/assets/oct5-11/mounting-motor-to-base.JPEG">

*To be revisited*

I was happy I got my prototype to be functional, but I thought it needed a little bit more *oomph*. I was tired though, I'd have to upgrade it tomorrow.

----------
### 10/8 - Acrylic records

I felt like my prototype was missing something aesthetically. I realized I wanted it to match the conceptual model of a turntable so people would have more intuition on how to interact with it. I decided to design "records" that I would laser cut out of acrylic sheets to give it more of that DJ vibe.

<img width="600" alt="" src="/assets/oct5-11/acrylic-vinyls.JPEG">

*[budgie beats](https://soundcloud.com/djbudgiebeats) is my DJ name*

I looked up the cost of acrylic at Jacobs and nearly cried, so I went to the scraps bin to see if anyone threw away their clear gold. I found a scrap 1/4" acrylic sheet; it was far too thick for what I was looking for (my plywood was 1/8" thick), but free is better, so I gave it a shot.

Oh, what a disaster that was. The acrylic melted horribly in the laser cutter after I had tried cutting through it twice with no luck.

<img width="600" alt="" src="/assets/oct5-11/acrylic-disaster.JPEG">

*I hope I didn't breathe that in...*

Luckily, someone in my cohort was gracious enough to share their 1/8" acrylic sheet with me that they had already purchased (I owe you one!!), and the cut went much better this time.

<img width="600" alt="" src="/assets/oct5-11/record-laser-cut-coating.JPEG">

<img width="600" alt="" src="/assets/oct5-11/acrylic-vinyls.JPEG">

*This was so satisfying to watch COUGH out of the corner of my eye*

I tested the acrylic records on the gears to see if they would spin, and it worked perfectly.

<img width="600" alt="" src="/assets/oct5-11/acrylic-gear-test.gif">

*Little celebration dance*

[Full video of gears spinning with acrylic records on top](/assets/oct5-11/acrylic-gear-test.MP4)

I did notice that the gears were somewhat uneven, so I would need to sand them down, but it was time for me to go home for the night.

----------
### 10/9 - Clean-up (fabrication and code)

I cleaned up my Arduino code using Gemini to fix the motor speed drop-off issue I was seeing before. Quoting Gemini directly:

> The DC motor doesn't spin at low speeds because your Arduino code is mapping the input speed range to an output range that starts at 60, effectively setting 60 as the minimum non-zero speed. You also have a dead-band (101 to 153) where the motor is explicitly stopped.

I used Gemini's suggestions, and sure enough, my motor could now spin at a crawling pace!

I continued my conversation with ChatGPT to clean up the p5.js code. Now the camera would be mirrored so it would match your expectations of where your hand would be in the camera view when you move it horizontally.

A major design decision that I made somewhat last minute was to add sound modulation to the code that would be controlled by the hand. I added this upon a suggestion from my classmate who saw my turntable and expected it to make a sound. I realized, it's code, I should be able to add sound, and sure enough, I could. Now, hand movement can also speed up and reverse the audio track that is loaded into the program at start time. So much more fun!

As for physical clean-up, I needed to sand down the 3D-printed motor mount. The cursed wood glue elevated the motor extender slightly too high! On second thought, I should have put it completely inside of the box and just mounted a dowel into the hole, aw well, too late.

I sanded down the mount using a pen sander since I didn't want to "gum up" the PLA filament (design specialist's words).

<img width="600" alt="" src="/assets/oct5-11/sanding-motor-mount.JPEG">

*Sanding parts smaller is frustratingly slow and a reminder to plan dimensions better*

It was worth the effort, because the vinyl record is not popping up and down anymore.

<img width="600" alt="" src="/assets/oct5-11/gears-more-even.JPEG">

*Still would have preferred to get the measurements right*

And with that, my prototype, which I lovingly named "Budgie Beats," was ready to hit the dance floor!

<img width="1000" alt="" src="/assets/oct5-11/budgie-beats-demo.gif">

*Wicky wicky wicky*

[Full video of budgie beats demo](/assets/oct5-11/elisa_lupin-jimenez_budgie_beats_demo.mp4)

<img width="600" alt="" src="/assets/oct5-11/budgie-beats-cover-photo.JPEG">
<img width="600" alt="" src="/assets/oct5-11/budgie-beats-final-1.JPEG">
<img width="600" alt="" src="/assets/oct5-11/budgie-beats-final-2.JPEG">
<img width="600" alt="" src="/assets/oct5-11/budgie-beats-final-3.JPEG">
<img width="600" alt="" src="/assets/oct5-11/budgie-beats-final-4.JPEG">
<img width="600" alt="" src="/assets/oct5-11/gears-lined-up.JPEG">
<img width="600" alt="" src="/assets/oct5-11/budgie-beats-underneath.JPEG">

Below are my diagrammatic analyses.

<img width="600" alt="" src="/assets/oct5-11/process-architecture-diagram.png">

*Process architecture diagram*

<img width="600" alt="" src="/assets/oct5-11/system-architecture-diagram.png">

*System architecture diagram*

- Here's my [ChatGPT query](https://chatgpt.com/share/68e3e2e9-822c-8010-9e35-796fe1ef163b) for writing the hands-off turntable code.
- Here's my [Gemini query](https://g.co/gemini/share/4bd36e495ac7) for resolving the DC motor dead-band issue.
- Here's my web-hosted p5.js [hands-off turntable sketch](https://editor.p5js.org/elisalj/sketches/I_wKH-S4d).

My learnings from this project:
- Don't be afraid to re-do cuts: it's not worth the time and effort to manually refine cuts when I could take a quarter of the time just changing the design digitally and recutting.
- Leave more space for error: my component base was way too tight, and everything was harder to work with because I had so little space to maneuver, especially when everything was mounted in place.
- Be patient with the wood glue: It takes time to set. Because I was messing around with the gears while the glue was still setting, I'm pretty sure I knocked the motor slightly out of place which ended up making my work so much harder to correct.

Excited for the next project!

----------

## Week 8
*(10/12 - 10/18)*

### 10/15 - Ideating on Ambient Display form

I teamed up with [Tala Salman](https://docs.google.com/document/d/1xAzELF5MhFs0jRcNGU2L16vmr_OXQ1GlwQGwzJs-xYw/edit?usp=sharing) to work on the Ambient Display project. We wanted to make a diffuse lamp that could give an artistic representation of live data. We looked into different API options for our project on this [public API listing on GitHub](https://github.com/public-apis/public-apis). We had considered using one of the art API resources such as the [Metropolitan Museum of Art Collection API](https://metmuseum.github.io/). We looked into display options that could be connected to our ESP32, then I remembered an old project that I worked on that also used a NeoPixel display and realized the [8x8 display](https://www.superlightingled.com/flex-8x8-led-matrix-display-panel-ws2815-rgb-light-for-signs-p-4908.html) we planned to use wouldn't have nearly high enough resolution to show any art meaningfully.

<img width="600" alt="" src="/assets/oct12-18/old-neopixel-project.JPEG">

*This is 16x16 and still looks like a potato instead of a dog*

We went back to the drawing board and looked into other APIs that could give us a live feed of data to modulate our visual board. After exploring the Open-Meteo API more, we discovered that they offered a [live data feed of localized marine weather](https://open-meteo.com/en/docs/marine-weather-api) in addition to general weather. We were inspired to use this wave feed to create a ripple effect on our screen that demonstrates wave period, direction, height, sea level height (for tides), and surface water temperature. We also explored a side-view versus a top-down view.

<img width="600" alt="" src="/assets/oct12-18/open-meteo-wave-api-online.png">

*This API gives hourly updates within a 5 km resolution*

<img width="600" alt="" src="/assets/oct12-18/wave-imagery-sketches.jpg">

*Side view versus top view of the ambient display*

<img width="600" alt="" src="/assets/oct12-18/wave-imagery-sketches-2.jpg">

*A hypothetical timelapse of the display from a top-down view*

<img width="600" alt="" src="/assets/oct12-18/ambient-display-sketch.JPEG">

*Container for display, potential ambient sheet?*

We will have to see how to implement this programmatically, but we are happy to have a direction to move towards.

----------

### 10/16 - Soldering the ESP32

To prepare for my next project, I needed to set up the ESP32, a more powerful microcontroller than the Arduino because it can access WiFi, among other processing improvements. In order to get the ESP32 board soldered in one shot, I went to Chris' solder jam session in Jacobs Makerspace. I started by sticking the two rows of pins directly into the breadboard, broke off the 3 pins I wouldn't need on the top left side of the board, then placed the board on top to make sure it was level.

<img width="600" alt="" src="/assets/oct12-18/line-up-pins.JPEG">

<img width="600" alt="" src="/assets/oct12-18/line-up-pins-2.JPEG">

*Lining up the pins on the breadboard with the ESP32*

Once everything looked lined up, I soldered the pins to the board one-by-one. I had to revisit several pins to get the teardrop shape that Chris recommended, but eventually I got there.

<img width="600" alt="" src="/assets/oct12-18/solder-pins-esp32.JPEG">

*Mid-solder*

<img width="600" alt="" src="/assets/oct12-18/completed-soldering-esp32.JPEG">

*Soldering is so satisfying*

Nice! Next step would be to set up the Arduino code.

----------

### 10/17 - Setting up the ESP32 code

I used the [ESP32 tutorial](https://github.com/loopstick/ESP32_V2_Tutorial?tab=readme-ov-file) to set up my Arduino IDE to compile and upload code to my new board. I installed the necessary drivers, updated the board manager URL in Arduino, and used [Blink_ESP32.ino](/scripts/Blink_ESP32.ino) to test if the connection was set up properly.

<img width="600" alt="" src="/assets/oct12-18/esp32-blink.gif">

*Flashback to the start of the semester*

[Full video of ESP32 blink](/assets/oct12-18/esp32-blink.MP4)

This was a simple setup process. The next part would be setting up a webAPI call. I can do that next week.

----------

## Week 9
*(10/19 - 10/25)*

### 10/20 - Making the weather API call on ESP32

I followed Roopa's [webAPI tutorial](https://github.com/roopa-ramanujam/ESP32-web-api-example) to set up the weather API usage on my ESP32. I configured my Berkeley net access portal to have the MAC address (which I saw whenever I flashed a sketch to the ESP32).

<img width="600" alt="" src="/assets/oct19-25/esp32-mac.png">

*It's not in the serial print though...*

<img width="600" alt="" src="/assets/oct19-25/berkeley-net-access-portal.png">

*Hope this works with the WiFI*

I realized that it would be an issue down the road if serial print was not working for me, so I took to [Gemini](https://gemini.google.com/share/ad0dc4029b7b) to figure out what was going wrong. Turns out that the MAC address calls were happening before serial and WiFi had time to initialize. I added some delay calls in the setup function, and it worked! Here's the updated [GetESP32MACAddress_v2.ino](/scripts/GetESP32MACAddress_v2.ino) sketch.

<img width="600" alt="" src="/assets/oct19-25/esp32-mac-fixed.png">

*Having print outs are the first step to debugging*

After this, I compiled [WiFiTest.ino](/scripts/WiFiTest.ino) with my home network and it worked beautifully.

The final test was to make a weather API call. I copied Roopa's [WeatherAPIExample.ino sketch](/scripts/WeatherAPIExample.ino), and it worked on the first try! Thanks Roopa for the great tutorial!

<img width="600" alt="" src="/assets/oct19-25/weather-api.gif">

*Perfect weather tonight*

[Full video of weather API call on ESP32](/assets/oct19-25/weather-api.MOV)

I'm pleased with this work for today.

----------
### 10/23 - Setting up the NeoPixel display

We wanted to upgrade to a NeoPixel 8x8 LED matrix. We followed the [Adafruit NeoPixel wiring guide](https://learn.adafruit.com/easy-neopixel-graphics-with-the-circuitpython-pixel-framebuf-library/wiring) to set up the matrix with a microcontroller. We stripped the main power and ground wires attached to the matrix and screwed them into a power adaptor, which we would need to supply 5V to the matrix.

<img width="600" alt="" src="/assets/oct19-25/neopixel-power-adaptor.jpg">

*It's my handy little screw-pen that I carry around*

We used the [Adafruit NeoPixel matrix test](/scripts/matrixtest.ino) that came with the [NeoPixel Matrix library](https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library) to test that the matrix wiring to the ESP32 was correct.

<img width="600" alt="" src="/assets/oct19-25/matrix-test.jpg">

*Worked the first time!*

Then, I vibe-coded a [basic ripple simulation](scripts/matrix-ripple-test.ino) to see what a circle expanding outward on the board would look like.

<img width="600" alt="" src="/assets/oct19-25/matrix-ripple-test.gif">

*It's basic but it should be good enough for testing*

[Full video of matrix ripple test](/assets/oct19-25/matrix-ripple-test.mp4)

Time for diffusion exploration!

----------
### 10/23 - Building the prototype for the ambient display holder

We knew we wanted to diffuse the harshness of the pixel display with something, but we weren't sure yet what material would achieve the desired ambient effect, so we looked around the Maker Space for spare parts.

<img width="600" alt="" src="/assets/oct19-25/testing-acrylic-frosting-against-monitor.jpg">

*Acrylic goes blurrrrrr*

We got a scrap piece of acrylic and used a buffer to add a frost diffusion effect, which we wanted to play around with to achieve the right visual effect for our otherwise harsh pixel board.

<img width="600" alt="" src="/assets/oct19-25/tala-sanding.jpg">

*She's having so much fun sanding away*

<img width="600" alt="" src="/assets/oct19-25/matrix-test.gif">

*Just an inch of space makes a big difference*

[Full video of matrix test with acrylic](/assets/oct19-25/matrix-test.mp4)

We continued to experiment with different grades of frosting and thickness of material.

<img width="600" alt="" src="/assets/oct19-25/graded-frosting.jpg">

<img width="600" alt="" src="/assets/oct19-25/weird-acrylic.jpg">

<img width="600" alt="" src="/assets/oct19-25/paper-diffusion.png">

*Already getting excited about this*

From there, we designed a laser cut for a rough prototype using cardboard so we could tolerance test the distance between our pixel board and the acrylic. We made the [prototype design file](/assets/oct19-25/cardboard-prototype-illustrator.png) in Illustrator.

<img width="600" alt="" src="/assets/oct19-25/cardboard-prototype-illustrator.png">

*The cardboard prototype on Illustrator*

<img width="600" alt="" src="/assets/oct19-25/laser-cut-cardboard.jpg">

*Laser cutting cardboard is so satisfying*

We glued the box together and started testing by sliding our piece of acrylic into the various slots at different heights above the LED matrix.

<img width="600" alt="" src="/assets/oct19-25/cardboard-prototype.jpg">

*Seeing a lot of variance just from the centimeter difference in spacing*

<img width="600" alt="" src="/assets/oct19-25/cardboard-prototype-another-angle.gif">

*Another angle in the cardboard prototype*

[Full video of cardboard prototype test](/assets/oct19-25/cardboard-prototype-another-angle.mp4)

<img width="600" alt="" src="/assets/oct19-25/l33t-h4ck3r.gif">

*Tapping away to a brighter future*

[Full video of coding ripple test](/assets/oct19-25/l33t-h4ck3r.mp4)

After playing around with the cardboard prototype, we liked the way the light diffused when it was lifted 5 centimeters above the board. Now that we had a better idea of the acrylic-board gap, it was time to make our code do what we actually wanted it to do.

----------
## Week 10
*(10/26 - 11/1)*

### 10/27 - Refining the NeoPixel matrix code

The first step in getting our ripple effect to work would be to set up the API calls using [Open-Meteo's Marine Weather API](https://open-meteo.com/en/docs/marine-weather-api). We decided to focus on just the wave height, wave period, and wave direction since we believed these parameters would interplay to give us the most interesting visual effect.

Building off of Roopa's [WeatherAPIExample.ino sketch](/scripts/WeatherAPIExample.ino), we worked with [Gemini](https://gemini.google.com/share/952c75304788) to create a first version of our API data visualization script. The main things I specified in the prompt, along with the [NeoPixel matrix example sketch](/scripts/matrixtest.ino) were to move the ripple in the wave direction received from the API (starting with North, West, East, and South), to adjust the brightness of the backdrop (which would remain a constant blue color) according to the height of the wave, and to make a new ripple according to the wave period (for instance, if the wave period is 5 seconds, we see a new ripple every 5 seconds). We weren't quite sure what we wanted to do with the height value yet, but figured the period and direction would be plenty to start with.

<img width="600" alt="" src="/assets/oct26-nov1/first-api-ripple.gif">

*Huh, the math for the board is wrong*

[Full video of first API call wave ripple](/assets/oct26-nov1/first-api-ripple.mp4)

We'd need to fix the mapping for the board, which we realized was wired in a zig-zag pattern.

<img width="600" alt="" src="/assets/oct26-nov1/fixed-ripple-line.gif">

*Better*

[Full video of first API call wave ripple](/assets/oct26-nov1/fixed-ripple-line.mp4)

We realized that with the wave period being so long, the screen would be black, so we decided to add a solid blue backdrop and use the API-fetched height value to adjust the brightness of the backdrop.

<img width="600" alt="" src="/assets/oct26-nov1/ripple-backdrop-blue.gif">

*More color, more bright*

[Full video of wave ripple with blue backdrop](/assets/oct26-nov1/ripple-backdrop-blue.mp4)

The culmination of this testing is contained in [ripple-effect-v1.ino](/scripts/ripple-effect-v1.ino).

After some deliberation, we decided to simplify our wave pattern since our 8x8 screen was too small to give good resolution to the wave curve. Instead of using a curve that is a symbolic wave, we decided to go more abstract and use a line that has pixels randomly shifted up and down to give the appearance of assymetry in waves crashing on a shore. This change can be seen in [ripple-effect-v2.ino](/scripts/ripple-effect-v2.ino), also coded with the assistance of [Gemini](https://gemini.google.com/share/a1fae9ae0fa8).

<img width="600" alt="" src="/assets/oct26-nov1/ripple-asymmetric-line.gif">

*This is much more visually appealing for a low-resolution display*

[Full video of wave ripple as line](/assets/oct26-nov1/ripple-asymmetric-line.mp4)

We weren't quite convinced with the blue backdrop being a strong enough signal of variance in wave height. We pivoted to representing wave height along the full-color spectrum, using a formula to convert wave height into a RGB values that can be displayed on the matrix. This change can be seen in `visualizeRipple()` inside [ripple-effect-v3.ino](/scripts/ripple-effect-v3.ino), also coded with the assistance of [Gemini](https://gemini.google.com/share/bca992c6a043). We adjusted the brightness by tweaking the values in the RGB algorithm in [ripple-effect-v4.ino](/scripts/ripple-effect-v4.ino).

Things were going well! Still, we had a lot of work ahead of us before we would be at museum quality, but time to go home.

----------
### 10/28 - More refinement of the NeoPixel

We revisited the "wave height to color algorithm" since we were seeing differences in brightness as separate red, green, and blue values imbalanced each other. We wanted a constant brightness for the lights even if the colors changed. We switched our algorithm to use hue, value, and saturation, since this would give us more control over the brightness while retaining the original intent of shifting through the color spectrum gradually according to the wave height. Now, the algorithm works by converting the wave height value into a fraction (we noticed that most waves we tracked around the world came in at under 5 meters, so we capped our wave height max at 5), then multiplying this with 48,000, which is the number of possible hues that our NeoPixel display could show. We also increased the directions that the wave could move in from 4 to 8, so now we captured North, Northeast, East, Southeast, South, Southwest, West, and Northwest. This change can be seen in [ripple-effect-v5.ino](/scripts/ripple-effect-v5.ino), also coded with the assistance of [Gemini](https://gemini.google.com/share/6cacdb4dc85b).

<img width="600" alt="" src="/assets/oct26-nov1/ripple-backdrop-hsv.gif">

*Looking a lot more fleshed out now*

[Full video of wave ripple with HSV color backdrop](/assets/oct26-nov1/ripple-backdrop-hsv.MOV)

We realized that Gemini had misordered the API direction to the visual movement so an API call of east was actually moving from the south, so we updated that manually in [ripple-effect-v6.ino](/scripts/ripple-effect-v6.ino)

We noticed that from some directions (such as when the wave came from the east), the ripple would stop short before disappearing. We fixed this by going through the different direction cases one-by-one and adjusting the limits specified.

Great progress here, time to get back to modifying the physical form of the piece.

----------
### 10/29 - Making the frame for the NeoPixel, adding struts to component frame

We built the case for the electronic components (the ESP32 and the NeoPixel) out of salvaged laser-cut black acrylic. We made the [case design](/assets/oct26-nov1/TDF%20Fabrication.dwg) using Rhino. We wanted to keep the case as small as possible so that it wouldn't stick out from the wall too far. We glued the case together using hot glue and tested our component fit. We also needed to cut away the extra breadboard, so we took a hacksaw to it.

<img width="600" alt="" src="/assets/oct26-nov1/case-dimensions-sketch.png">

*Measuring dimensions for case to fit components*

<img width="600" alt="" src="/assets/oct26-nov1/cutting-breadboard.jpg">

*Sliced bread(board)*

<img width="600" alt="" src="/assets/oct26-nov1/tala-rhino.jpg">

*Look at her go on Rhino*

<img width="600" alt="" src="/assets/oct26-nov1/case-design.png">

*Sleek case*

<img width="600" alt="" src="/assets/oct26-nov1/case-pieces.png">

*Gluing it together*

<img width="600" alt="" src="/assets/oct26-nov1/black-case.jpg">

*Fits like a glove*

We wanted to suspend the piece of acrylic in the air, so our structural support needed to be minimal. We found metal servo hooks lying around the Makerspace and, due to the little hook at the end, used them as a tension hold for the acrylic piece. We used a power drill to make four holes in the top of the case, then cut the servo hooks to the right length so we could suspend our acrylic piece 5 cm above the LED matrix.

<img width="600" alt="" src="/assets/oct26-nov1/drill-strut-hole.jpg">

*Drill, baby drill!*

<img width="600" alt="" src="/assets/oct26-nov1/struts-in-place.jpg">

<img width="600" alt="" src="/assets/oct26-nov1/struts-in-place-2.jpg">

*Starting to look like our final vision*

We noticed there were slight gaps along the sides of the NeoPixel still, so we decided to laser cut an additional frame to place on top of the original case. This would help cover the gaps and also hold the NeoPixel in place, which would be essential when we mount the device to the wall so the NeoPixel doesn't slip downward.

<img width="600" alt="" src="/assets/oct26-nov1/frame-add">

*This looks even better than before*

At this moment, we realized we were missing a capacitor for the circuit, which was recommended in the library, so we added one it before we glued all the frame parts together.

<img width="600" alt="" src="/assets/oct26-nov1/capacitor.jpg">

*That could have been a woopsie if we had a power surge run through our device*

We popped the acrylic diffuser into place, and voila! The Ripple Effect is alive!

<img width="600" alt="" src="/assets/oct26-nov1/fully-assembled-first-time.gif">

*Looking a lot more fleshed out now*

[Full video of first assembly](/assets/oct26-nov1/fully-assembled-first-time.mp4)

So close to demo day! But we were feeling confident about wrapping up the final touches tomorrow.

----------
### 10/30 - Final code adjustments and demo

In [ripple-effect-v7.ino](/scripts/ripple-effect-v7.ino), we cleaned up the comments, added a header explaining what "The Ripple Effect" does, and added more coordinates for locations around the world that had interesting wave patterns.

We updated this to [ripple-effect-final.ino](/scripts/ripple-effect-final.ino) to be the in-home experience we hoped for our piece. We imagined a person could load in the coordinates of any location they have a special connection with and The Ripple Effect would show them what the shores of that location looks like in any given moment.

Of course... we realized this may not be too interesting for our demo, since wave patterns don't change drastically over the course of an hour, so we adapted our code into a "demo mode" that would cycle between locations every 7 seconds. This was to demonstrate the versatility and responsiveness of our piece. This change can be seen in [ripple-effect-demo-mode-dual-core.ino](/scripts/ripple-effect-demo-mode-dual-core.ino), also coded with the assistance of [Gemini](https://gemini.google.com/share/581a8546825c). The main update from our original [ripple-effect-demo-mode.ino](/scripts/ripple-effect-demo-mode.ino) that we developed first was that we now took advantage of the dual core present in the ESP32 to have multi-threaded functionality. Basically, by using a second core in our code to make the API call, we removed the blocker that the `http.GET()` call made in the `loop()` function.

All that was left was to mount it to the wall and give our demo! (Thanks command strips)

<img width="600" alt="" src="/assets/oct26-nov1/mounted-on-wall.gif">

*Now this is the mother of all demos! jk*

More photos of "The Ripple Effect" below.

<img width="600" alt="" src="/assets/oct26-nov1/ripple-effect-1.JPG">

<img width="600" alt="" src="/assets/oct26-nov1/ripple-effect-2.JPG">

<img width="600" alt="" src="/assets/oct26-nov1/ripple-effect-3.JPG">

<img width="600" alt="" src="/assets/oct26-nov1/ripple-effect-4.JPG">

<img width="600" alt="" src="/assets/oct26-nov1/ripple-effect-5.JPG">

<img width="600" alt="" src="/assets/oct26-nov1/ripple-computer.gif">

[Link to "The Ripple Effect" demo video](https://drive.google.com/file/d/1LGKpT4Vu-hRFUr1Gi2ScmGSBeP3CM565/view?usp=sharing)

For the diagrammatic analyses, I made a process architecture diagram and a system architecture diagram. I also played around with [Liminal](https://theliminal.design/), a concept map generation app made by my TA from another class [Lingxiu](https://design.berkeley.edu/profiles/lingxiu) to see if it could make a good representation of how our ripple effect system works.

<img width="600" alt="" src="/assets/oct26-nov1/ripple-process-diagram.png">

*Process architecture diagram*

<img width="600" alt="" src="/assets/oct26-nov1/ripple-system-diagram.png">

*System architecture diagram*

<img width="600" alt="" src="/assets/oct26-nov1/liminal-systems-diagram-ripple.png">

*Liminal-generated diagrammatic analysis*

Wow! This must be my favorite project that I've worked on so far. My reflections are mainly that the work is so much smoother when I work with a complementary expert such as Tala. She taught me so much about efficient CAD, the importance of early prototypes and testing out many different materials to get the best results. In turn, I showed Tala a lot about how to read code, understand API usage, and set up more complex circuits. We made a great team, and our work proves that together we are stronger.

----------
## Week 11
*(11/2 - 11/8)*

### 11/4 - Developing individual final project proposal, forming a final project team

In preparation for the final project, I thought about a few ways I could squeeze [TouchDesigner](https://derivative.ca/) into my project because I knew I wanted to learn TouchDesigner but needed a good excuse to integrate it into the technology I had already learned about in TDF. I decided on an idea called "ContactDesigner," a wearable device that maps movement to a visual generated within TouchDesigner. The idea was to take away the pressure associated with collaborative dance (in some circles called [Contact Improv](https://youtu.be/TbjUPAaqkPQ)) by incorporating kinetic feedback into a visual layer. I hoped that through this visual feedback, people who wanted to dance would be able to lean into the playfulness of the visuals and thus feel more disinhibited to express themselves. I imagined the technology being a hybrid physical/digital interface that would require some fabrication to develop the wearable parts and microcontroller/sensor investigation to support the processing of kinetic data.

<img width="600" alt="" src="/assets/nov2-8/poster-pitch.png">

*Final project pitch poster*

I took my poster to class, where we presented our individual project posters and reviewed them to find potential collaborators for our final project. I joined forces with [Tala Salman](https://docs.google.com/document/d/1xAzELF5MhFs0jRcNGU2L16vmr_OXQ1GlwQGwzJs-xYw/edit?usp=sharing) and [Paola Rodriguez Vitale](https://www.notion.so/272651e0c798804a8e60c43801d321c3?v=272651e0c79880ad9afe000ca3558b5f) since we were all interested in learning how to use TouchDesigner.

<img width="600" alt="" src="/assets/nov2-8/posters-group.jpg">

*Pitch posters from group, assimilating ideas*

### 11/6 - Developing group project proposal

Tala, Paola, and I started planning for our group project proposal. We decided to narrow in on a stress-regulating device that uses visuals to encourage mindfulness. We collected several sensors from our kit: the IMU accelerometer/gyroscope sensor, a haptic motor driver, and the ESP32. Even though we hadn't used these sensors in previous projects, we felt that they had good documentation and would serve well for our physical device. We made some sketches for the potential interactions a user could have with our device.

-----------
## Week 12
*(11/9 - 11/15)*

### 11/10 - Submitting the group proposal

We wrapped up our [group proposal](https://docs.google.com/document/d/1tfLhcnEpaDdaBUoIEFkYbC_vqF9axVl7gGg9VvHPZ84/edit?usp=sharing). Our working project name was "PET Project," a play on words and an acronym of our names, and our working idea was to map embodied motion of a user to dynamic visuals rendered in TouchDesigner through a handheld physical device.

Our components would include a screen (either a monitor or projector, but something with high resolution), TouchDesigner, computer vision via p5.js, the [ESP32 Feather V2](https://learn.adafruit.com/adafruit-esp32-feather-v2), the [MPU 6050 IMU sensor](https://www.adafruit.com/product/3886), and the [DA7280 Haptic Driver](https://www.sparkfun.com/sparkfun-qwiic-haptic-driver-da7280.html).

We imagined use cases for PET project as the following:
- A single user regulates their stress through intentional movement with our device that provides engaging visual feedback.
- An artist uses our device as a medium to convey synesthetic movement to an audience.
- An installation device used for meditation.  
- A collective or individual biofeedback installation.
- Multiple users collaboratively play with our device (or multiple devices) to “paint” on a digital canvas.

We also proposed six experiments to guide us in our process to reaching the final product:
1. IMU calibration + filtering
2. Testing the serial communication between TouchDesigner & ESP32
3. Mock ESP32 sensor data to TD and design a dynamic visual
4. Building the visual interface and Haptic Feedback
5. Alternative Motion Input Testing via p5.js
6. Physical Form - Enclosure Prototype Test

We also created a system architecture for our proposal.

<img width="600" alt="" src="/assets/nov9-15/proposal-system-architecture.png">

*Proposed system architecture for PET project*

[Full PDF of proposal available here](/assets/nov9-15/PET%20Project%20Proposal%20-%20Elisa,%20Tala,%20Paola.pdf)

We had our work cut out for us, but at least we had some places to start!

### 11/13 - Testing the IMU sensor

I started with an unsoldered MPU 6050 IMU sensor.

<img width="600" alt="" src="/assets/nov9-15/mpu-pre-solder.jpg">

*IMU sensor before soldering*

<img width="600" alt="" src="/assets/nov9-15/mpu-post-solder.jpg">

*IMU sensor after soldering*

I followed this [Adafruit guide](https://learn.adafruit.com/mpu6050-6-dof-accelerometer-and-gyro/arduino) to set up the wiring with the ESP32.

I tested the IMU gyroscope and accelerometer with [imu_basic_test.ino](/scripts/imu_basic_test.ino), and it worked just as expected!

<img width="600" alt="" src="/assets/nov9-15/imu_test.jpg">

*IMU wiring*

<img width="600" alt="" src="/assets/nov9-15/imu-test.gif">

*Quite responsive!*

[Link to IMU test full video](/assets/nov9-15/imu-test.mp4)

I updated the basic test into a new sketch [imu_motion_detection.ino](/scripts/imu_motion_detection.ino) that printed out a serial string with accelerometer and gyroscope data. I then set up TouchDesigner to read this serial printed data, and it pretty much worked out of the box using a Serial DAT operator. I used [Gemini](https://gemini.google.com/share/02e3a5b47374) to help me set up this Touch node network (called a patch). 

<img width="600" alt="" src="/assets/nov9-15/td-esp32-connection.png">

*Serial DAT operator reading ESP32 printouts*

<img width="600" alt="" src="/assets/nov9-15/imu-touch.gif">

*Plug and chug!*

[Link to IMU TouchDesigner test full video](/assets/nov9-15/imu-touch.mp4)

----------

Later that day, Tala, Paola, and I took a trip to the Exploratorium for inspiration on visuals and physical interactions.

<img width="600" alt="" src="/assets/nov9-15/team-at-explo.jpg">

*Field trip!*

We stumbled upon this exhibit which felt like the vibe we wanted to go for. It was a huge projection displaying some sort of vapor, and the vapor would drift based on the knobs being turned. We liked the size of the experience and the ambience of the vapor drifting across the screen.

<img width="600" alt="" src="/assets/nov9-15/explo.jpg">

*Nice and ambient*

----------
## Week 13
*(11/16 - 11/22)*

### 11/17 - Setting up the haptic driver

Filled with determination, I set up the haptic driver with the ESP32. I used a [SparkFun guide](https://learn.sparkfun.com/tutorials/qwiic-haptic-driver-da7280-hookup-guide) to use the I2C (a serial, two-wire communication protocol used for short-distance communication between integrated circuits) so later I would not need to use a breadboard or a protoboard for the sensors.

I tried connecting the I2C wire from the ESP32 to the haptic driver and ran [I2C_mode.ino](/scripts/I2C_mode.ino) but it didn't power up. I troubleshooted by plugging some jumper wires into my breadboard and holding them in the right pins, then it lit up.

<img width="600" alt="" src="/assets/nov16-22/haptic-manual-wiring.png">

*So the component isn't defective...*

I troubleshooted a bit and discovered that I needed to manually pull the power pin high in the code for I2C to work on the ESP32 (thanks [Adafruit](https://learn.adafruit.com/adafruit-esp32-feather-v2?view=all#stemma-qt-connector-3112257) for the detailed explanation on power modes).

I connected the IMU sensor and the haptic driver together using I2C, then I used [Gemini](https://gemini.google.com/share/34327ef22b0c) to merge the haptic driver example and IMU sensor example, contained in [imu_motion_haptic.ino](/scripts/imu_motion_haptic.ino)

<img width="600" alt="" src="/assets/nov16-22/imu-haptic-test.gif">

*All of our components working together*

[Link to IMU haptic test full video](/assets/nov16-22/imu-haptic-test.mp4)

I cleaned up the code a bit so that the haptic feedback would be a bit more fluid, as seen in [imu_motion_haptic_v2.ino](/scripts/imu_motion_haptic_v2.ino).

### 11/18 - Initial prototypes for the device case

We wanted to get a sense for how small we could make our device to enclose all the necessary components. We taped all our pieces together to a cardboard cutout

<img width="600" alt="" src="/assets/nov16-22/taped-components.jpg">

*We could get it pretty thin, but the battery takes up the greatest area*

We crafted a small finger-joint box to fit around the components (thanks Paola for CADing that up!)

<img width="600" alt="" src="/assets/nov16-22/components-box.jpg">

*Not as small as we hoped...*

The box felt fairly bulky, but everything fit inside. We would have to try more prototypes out to get the right hand-feel for our device.

### 11/20 - Setting up WiFi connectivity

I read the [Derivative forum](https://forum.derivative.ca/t/how-to-send-sensor-data-to-touchdesigner-using-esp32/150215/4) for information about sending signals to TouchDesigner via WiFi since we wanted our device to be completely wireless to allow for more freedom of movement. After consulting the forum and [Gemini](https://gemini.google.com/share/be968218553a), I decided to move forward with UDP (User Datagram Protocol) because we only needed a one-way data stream (from ESP32 to TouchDesigner), and it would be more straightforward to set up than WebSockets, the other option.

After some trial and error with our code in [imu_motion_haptic_wifi.ino](/scripts/imu_motion_haptic_wifi.ino), we were able to get the ESP32 to send the IMU data wirelessly, which required me to use hotspot so that both my computer and the ESP32 operated on the same WiFi, a requirement for using UDP.

<img width="600" alt="" src="/assets/nov16-22/wifi-test.gif">

*Sending data wirelessly is working!!!*

[Link to WiFi test full video](/assets/nov16-22/wifi-test.mp4)

[Link to TouchDesigner file](/scripts/touchdesigner/esp_wifi_test.toe)

### 11/21 - Testing container shapes

We measured the dimensions of our components, then we sketched our component layout. We wanted our components to go into each half of the container, which could be closed like a clam shell

<img width="600" alt="" src="/assets/nov16-22/component-layout-sketch.jpg">

*Top and side views*

We then sketched some options for the outside aesthetic of the case.

<img width="600" alt="" src="/assets/nov16-22/outside-sketches.jpg">

*Perhaps something evoking a cuddlefish?*

We laid our components on a piece of paper and sketched around them to get a more realistic sense of the layout and sizing of the container.

<img width="600" alt="" src="/assets/nov16-22/sketch-around-components.jpg">

*Looking a bit computer mouse-like*

We then cut out a couple ovals in cardboard and wrapped them around our components to get a feel for how our device would handle with this shape.

<img width="600" alt="" src="/assets/nov16-22/cardboard-ovals.jpg">

*Feels better than the box already*

We tried a few cardboard shapes to see if one felt better than another, using Illustrator to precisely laser-cut them.

<img width="600" alt="" src="/assets/nov16-22/cardboard-ovals-2.jpg">

<img width="600" alt="" src="/assets/nov16-22/cardboard-ovals-3.jpg">

*The more organic shape felt the best*

We taped around the organic shape to give the prototype contour.

<img width="600" alt="" src="/assets/nov16-22/taped-oval.jpg">

*Now that's a promising hand-feel*

----------
## Week 14
*(11/23 - 11/29)*

### 11/24 - Carving our project case out of wood

Feeling confident about the shape of our prototype, we cut out some blocks of wood that we could later carve with the table saw.

<img width="600" alt="" src="/assets/nov23-29/table-saw.jpg">

*Look at that form*

We then sliced our block of wood in half with a band saw so that we could drill out a pocket in the middle of each half to fit the components.

<img width="600" alt="" src="/assets/nov23-29/band-saw.jpg">

*Hm, maybe that's not my hand...*

Then we used the drill press to carve out the inner pocket hole by hole.

<img width="600" alt="" src="/assets/nov23-29/drill-press.jpg">

*This takes way too long*

We finished making the pocket for one half of the wood block and tested fitting our components inside to see if we could feel the vibration through the wood.

<img width="600" alt="" src="/assets/nov23-29/components-in-pocket.jpg">

*Halfway there*

We couldn't be "pressed" (hah) to go through another drill press iteration, so we switched to using an impact driver with the hole-cutter bit.

<img width="600" alt="" src="/assets/nov23-29/get-er-done.jpg">

*Had to take things into my own hands*

We fit the components into each of the pockets and tested the clam shell fit.

<img width="600" alt="" src="/assets/nov23-29/components-in-each-pocket.jpg">

*Making progress*

### 11/25 - Placing magnets into the shell

We wanted the halves to snap together using magnets, so we taped magnets of different sizes to the halves to see which would have the best hold.

<img width="600" alt="" src="/assets/nov23-29/magnets.jpg">

<img width="600" alt="" src="/assets/nov23-29/magnets-2.jpg">

*It worked*

We used the drill press again to get the precise diameter and depth of the hole to fit our magnets.

<img width="600" alt="" src="/assets/nov23-29/drill-press-magnets.jpg">

*Such a heavy-duty machine for what seems like a simple task...*

We superglued the magnets into place, then we sawed off the edges around the shape we had drawn into the wood blocks. We taped the halves together, then we used the belt sander to carve out the perfect shape for our container.

<img width="600" alt="" src="/assets/nov23-29/belt-sander.jpg">

*A risky maneuver but we got there*

<img width="600" alt="" src="/assets/nov23-29/belt-sander.gif">

*Carving out the sides*

[Link to belt sander full video](/assets/nov23-29/belt-sander.mp4)

<img width="600" alt="" src="/assets/nov23-29/before-after-sanding.jpg">

<img width="600" alt="" src="/assets/nov23-29/before-after-sanding-2.jpg">

*Before and after we carved the sides out*

The form of our project was nearly complete! We would just need to put the final touches on it with some hand sanding and wood stain.

<img width="600" alt="" src="/assets/nov23-29/finished-carving.gif">

*Looks like we pulled it out of the river*

[Link to belt sander full video](/assets/nov23-29/finished-carving.mp4)

### 11/26 - Wood staining the container

This was a quick step in our process, but an essential one aesthetically. We added a wood stain paint to bring out the natural rings in our wood block.

<img width="600" alt="" src="/assets/nov23-29/wood-stain.jpg">

*It really pops now!*

### 11/29 - Refining IMU sensor

I worked on updating the haptic feedback to flow more continuously because in the previous script it would stop mid-movement. I switched the logic with help from [Gemini](https://gemini.google.com/share/d90b1d460ae7) so that the haptic driver would always vibrate unless no movement was detected, which ended up working better. The sketch is [imu_motion_haptic_wifi_v2.ino](/scripts/imu_motion_haptic_wifi_v2.ino).

<img width="600" alt="" src="/assets/nov23-29/continuous-vibes.gif">

*Much better*

[Link to continuous vibration full video](/assets/nov23-29/belt-sander.mp4)

----------
## Week 15
*(11/30 - 12/6)*

### 12/2 - Fixing the components into the shell

We screwed in our components into the pocket of the carved wood using a regular screwdriver (since the wood was soft enough to do so).

<img width="600" alt="" src="/assets/nov30-dec6/screwing-in.jpg">

*Don't mess with a person who can use a screwdriver*

<img width="600" alt="" src="/assets/nov30-dec6/screwed-components.jpg">

*Nice and fixed*

<img width="600" alt="" src="/assets/nov30-dec6/snap-fit.gif">

*Snap fit*

[Link to snap fit full video](/assets/nov30-dec6/snap-fit.mp4)

### 12/3 - Last-minute IMU sensor calibration

I realized I had not properly calibrated the IMU sensor yet. Luckily, Jeff provided me with a [calibration script](/scripts/mpu6050_calibration2.ino) that would persist in the ESP32 memory. I updated my code with these calibration offset values and output roll and pitch values, as seen in [imu_motion_haptic_wifi_v3.ino](/scripts/imu_motion_haptic_wifi_v3.ino).

### 12/5 - More IMU sensor refinement

I wanted to take the IMU readings to the next level by using the accelerometer and gyroscope data in combination to determine the translational movement of the device. As it turns out, this is an extremely difficult problem to solve given limited sensors in a process called "dead reckoning," where one must integrate acceleration data over time precisely or else the device will "drift." After spending several hours troubleshooting this with the help of [Gemini](https://gemini.google.com/share/a9c9bb723063) and examining the [official MPU 6050 specification document](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf), I gave up on [this sketch](/scripts/imu_motion_haptic_wifi_v5_not_working.ino) and settled for [imu_motion_haptic_wifi_v4.ino](/scripts/imu_motion_haptic_wifi_v4.ino) which would output a rotational state in addition to the pitch and roll values. Using Tala's work on the [TouchDesigner file](/scripts/touchdesigner/Tala_PET_jml.8.toe), I integrated the pitch and roll values and mapped them to x and y coordinates.

<img width="600" alt="" src="/assets/nov30-dec6/touch-initial-visual-imu.gif">

*Moves the particles beautifully*

[Link to touch visual testing full video](/assets/nov30-dec6/touch-initial-visual-imu.mp4)

We played around more with the particle effects to find the right movement/color schemes.

<img width="600" alt="" src="/assets/nov30-dec6/touch-colors-1.gif">

*Rainbow*

[Link to touch colors full video](/assets/nov30-dec6/touch-colors-1.mp4)

<img width="600" alt="" src="/assets/nov30-dec6/touch-colors-2.gif">

*Ocean*

[Link to touch colors full video](/assets/nov30-dec6/touch-colors-2.mp4)

[TouchDesigner final file](/scripts/touchdesigner/flow.toe)

----------
## Week 16
*(12/7 - 12/12)*

### 12/7 - Testing bases for the device

We made a few CAD models for the base that would present our device. We compared several options side-by-side for stability and aesthetic.

<img width="600" alt="" src="/assets/dec7-12/bases.jpg">

*We love a good iteration*

We moved forward with the black circular stand because we wanted to create a strong visual contrast with the light wood of our device. Having the gap in the front ledge of the device prevented it from looking like a smiley face.

<img width="600" alt="" src="/assets/dec7-12/base-cad.png">

*A sleek finish for a sleek device*

### 12/8 - Preparing for the showcase

<img width="600" alt="" src="/assets/dec7-12/flow-2.JPG">

*Our final product: flow*

We brought our device which we finally named "flow" up to the showcase room and tested it on the projector screen.

<img width="600" alt="" src="/assets/dec7-12/flow-projector.gif">

*flow looks beautiful when it's massive!*

Ultimately, we needed to downsize to a monitor since we would be sharing the showcase room with other teams, so we migrated our setup to a side room.

<img width="600" alt="" src="/assets/dec7-12/flow-monitor.gif">

*flow still looks really cool even on the smaller screen*