# Technology Design Foundations Journal
Hello! I'm an MDes student at UC Berkeley, and this is my design journal for "DESINV 202: Technology Design Foundations." I will keep track of my progress per week below:

*No journal entries for Week 1*  
[Week 2](#week-2)  
[Week 3](#week-3)  
[Week 4](#week-4)  
[Week 5](#week-5)  
[Week 6](#week-6)  
[Week 7](#week-7) 

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
*(10/5 - 10/12)*

### 10/6 - Playing around with p5.js

After playing around with Dr. Sudhu's ["happy little skies" sketch](https://openprocessing.org/sketch/2584640) on the OpenProcessing website and his [DC motor p5.js sketch](https://editor.p5js.org/loopstick/sketches/MWZxoSNoP) on the p5.js online editor, I wanted to try setting up a simple computer vision sketch for eye tracking. Sadly, I quickly discovered via ChatGPT that the computer vision model that we would use is not sensitive enough to detect eye position. I still wanted to do something that played around with a different motion than ear positions, so I decided to explore hand movement.

I started by trying to detect two hands, where each hand can determine the summed speed, but I got wonky behavior when I had two hands up, so I limited the detection to just one hand.

<img width="600" alt="" src="/assets/oct5-12/cv-hands-first-test.gif">

*GIF of hand tracking motor test*

[Full video of hand tracking motor test](/assets/oct5-12/cv-hands-first-test.MP4)

One thing I noticed with the code is that the motor doesn't start spinning until it detects a value over 25, so I would need to figure out what was going on here, but that would be a later problem.

----------
### 10/7 - Making the turntable gears

Back to the fabrication portion of my project, I designed the gears in Fusion using the [Spur Gear Add-In](https://productdesignonline.com/fusion-360-tutorials/create-custom-3d-printable-gears-in-fusion-360/#:~:text=Accessing%20the%20Spur%20Gear%20Add,matter%20which%20one%20you%20choose.) that I had wanted to use for my [laser-cut ring project from earlier](### 9/18 - Second pass on 3D-printed ring). I measured the dimensions of the square portion on the 3D-printed peg that came with my DC motor to make a cut-out in the gear that would actuate the system, and I made the gear have the diameter of the hole that I cut out so it would be flush with the peg. I also measured the diameter of the dowel.

<img width="600" alt="" src="/assets/oct5-12/measuring-square-peg.JPEG">

<img width="600" alt="" src="/assets/oct5-12/measuring-square-peg.JPEG">

<img width="600" alt="" src="/assets/oct5-12/small-spur-gears-fusion.png">

*Looking good so far*

I added two larger gears to serve as the base for the records on the turntable, being careful to make the teeth on all the gears the same size and distance apart so they would fit together neatly. I also added in holes into the gears not connected directly to the motor that would fit a dowel. I then exported the Fusion sketch as [a .dxf file](/assets/oct5-12/expressive-mechanics-gears.dxf) into Illustrator and laid out the gears to be cut neatly into a plywood piece.

<img width="600" alt="" src="/assets/oct5-12/all-spur-gears-fusion.png">

<img width="600" alt="" src="/assets/oct5-12/all-spur-gears-illustrator.png">

*Hopefully the geometry is correct...*

Unfortunately, the laser cutter unexpectedly disconnected four minutes into the job, so I was left with jagged-edged gears.

<img width="600" alt="" src="/assets/oct5-12/broken-gears.JPEG">

*We were so close!*

I still wanted to make use of the messed-up gears, though, so I tested the spinning mechanic with the motor by holding it in place.

<img width="300" alt="" src="/assets/oct5-12/testing-gear-mechanic.gif">

*GIF of gear mechanic test*

[Full video of gear mechanic test](/assets/oct5-12/testing-gear-mechanic.MP4)

Feeling more confident that my design would work, I ran the laser cut again and got a perfect gear cut this time.

<img width="600" alt="" src="/assets/oct5-12/gears-laser-cut.JPEG">

*Woohoo*

I sanded the gears to remove the burn marks, then I got to work on the base board. I realized I was pretty unhappy with the splintered wood in my original base plate, so I redesigned the [base board file](/assets/sept30-oct4/makercase-with-layout-back-fixed.ai) to incorporate the holes for the dowels.

<img width="600" alt="" src="/assets/oct5-12/new-base-board-illustrator.png">

*More respectable*

After recutting the board, I was much more happy with the results; it was well-worth the effort to re-do.

<img width="600" alt="" src="/assets/oct5-12/before-after-base.JPEG">

*What a difference*

Then, I mounted all the components into place.

<img width="600" alt="" src="/assets/oct5-12/components-fixed-to-base.JPEG">

*A little cleanup required*

I squeezed the dowels into the holes of the base board, only to realize if my gears rested directly on the base board, there would be too much friction for them to spin smoothly. As a solution, I designed some [wooden "standoffs"](/assets/oct5-12/gear-standoffs.ai) for my gears to give them some lift off of the platform.

<img width="600" alt="" src="/assets/oct5-12/gear-standoffs.JPEG">

*It's a tight fit*

Unfortunately, I didn't account for slightly discrepancies in measurements, so the holes in my baseboard were slightly too small for the dowels. I first used a hand drill to open up the holes in the gears, then I attached the dowel as an attachment to the hand drill to sand down the dowels by holding the sandpaper around the spinning dowel.

<img width="600" alt="" src="/assets/oct5-12/opening-up-dowel-holes.JPEG">

*Maybe laser-cutting again would have been faster...*

Once the dowels could squeeze into the platform holes, I cut the dowels to be just tall enough to give the gears clearance from the platform and the 3D-printed motor peg.

<img width="600" alt="" src="/assets/oct5-12/placing-dowels-in-base.JPEG">

*It's really coming together now*

I placed the gears onto the dowels and tested out the motor, holding the base board and motor in place.

<img width="600" alt="" src="/assets/oct5-12/gears-spinning-first-time.gif">

*IT'S WORKING*

[Full video of gears mechanically spinning for the first time](/assets/oct5-12/gears-spinning-first-time.MP4)

An important side-note: I realized I had messed up my gear math. I thought my bigger gears would rotate in the same direction, but it turns out I messed up in my original sketch, so now they rotate toward and away from each other. Aw well, iT'S a FeAtUrE, nOt A bUg.

Confident with my rig, I hot-glued the dowels in place. I used wood blocks to lift the motor up along the side wall so that just the square peg on the 3D-printed motor mount would stick out of the hole. I drilled the 3D-printed motor case to the wood block, then I wood glued the block to the side wall of the component case. It was difficult to get the motor mount to be perfectly level with the box, so I had to hope it would stick in the right place.
  
<img width="600" alt="" src="/assets/oct5-12/mounting-motor-to-base.JPEG">

*To be revisited*

I was happy I got my prototype to be functional, but I thought it needed a little bit more *oomph*. I was tired though, I'd have to upgrade it tomorrow.

----------
### 10/8 - Acrylic records

I felt like my prototype was missing something aesthetically. I realized I wanted it to match the conceptual model of a turntable so people would have more intuition on how to interact with it. I decided to design "records" that I would laser cut out of acrylic sheets to give it more of that DJ vibe.

<img width="600" alt="" src="/assets/oct5-12/acrylic-vinyls.JPEG">

*[budgie beats](https://soundcloud.com/djbudgiebeats) is my DJ name*

I looked up the cost of acrylic at Jacobs and nearly cried, so I went to the scraps bin to see if anyone threw away their clear gold. I found a scrap 1/4" acrylic sheet; it was far too thick for what I was looking for (my plywood was 1/8" thick), but free is better, so I gave it a shot.

Oh, what a disaster that was. The acrylic melted horribly in the laser cutter after I had tried cutting through it twice with no luck.

<img width="600" alt="" src="/assets/oct5-12/acrylic-disaster.JPEG">

*I hope I didn't breathe that in...*

Luckily, someone in my cohort was gracious enough to share their 1/8" acrylic sheet with me that they had already purchased (I owe you one!!), and the cut went much better this time.

<img width="600" alt="" src="/assets/oct5-12/record-laser-cut-coating.JPEG">

<img width="600" alt="" src="/assets/oct5-12/acrylic-vinyls.JPEG">

*This was so satisfying to watch COUGH out of the corner of my eye*

I tested the acrylic records on the gears to see if they would spin, and it worked perfectly.

<img width="600" alt="" src="/assets/oct5-12/acrylic-gear-test.gif">

*Little celebration dance*

[Full video of gears spinning with acrylic records on top](/assets/oct5-12/acrylic-gear-test.MP4)

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

<img width="600" alt="" src="/assets/oct5-12/sanding-motor-mount.JPEG">

*Sanding parts smaller is frustratingly slow and a reminder to plan dimensions better*

It was worth the effort, because the vinyl record is not popping up and down anymore.

<img width="600" alt="" src="/assets/oct5-12/gears-more-even.JPEG">

*Still would have preferred to get the measurements right*

And with that, my prototype, which I lovingly named "Budgie Beats," was ready to hit the dance floor!

<img width="1000" alt="" src="/assets/oct5-12/budgie-beats-demo.gif">

*Wicky wicky wicky*

[Full video of budgie beats demo](/assets/oct5-12/elisa_lupin-jimenez_budgie_beats_demo.mp4)

<img width="600" alt="" src="/assets/oct5-12/budgie-beats-cover-photo.JPEG">
<img width="600" alt="" src="/assets/oct5-12/budgie-beats-final-1.JPEG">
<img width="600" alt="" src="/assets/oct5-12/budgie-beats-final-2.JPEG">
<img width="600" alt="" src="/assets/oct5-12/budgie-beats-final-3.JPEG">
<img width="600" alt="" src="/assets/oct5-12/budgie-beats-final-4.JPEG">
<img width="600" alt="" src="/assets/oct5-12/gears-lined-up.JPEG">
<img width="600" alt="" src="/assets/oct5-12/budgie-beats-underneath.JPEG">

Below are my diagrammatic analyses.

<img width="600" alt="" src="/assets/oct5-12/process-architecture-diagram.png">

*Process architecture diagram*

<img width="600" alt="" src="/assets/oct5-12/system-architecture-diagram.png">

*System architecture diagram*

- Here's my [ChatGPT query](https://chatgpt.com/share/68e3e2e9-822c-8010-9e35-796fe1ef163b) for writing the hands-off turntable code.
- Here's my [Gemini query](https://g.co/gemini/share/4bd36e495ac7) for resolving the DC motor dead-band issue.
- Here's my web-hosted p5.js [hands-off turntable sketch](https://editor.p5js.org/elisalj/sketches/I_wKH-S4d).

My learnings from this project:
- Don't be afraid to re-do cuts: it's not worth the time and effort to manually refine cuts when I could take a quarter of the time just changing the design digitally and recutting.
- Leave more space for error: my component base was way too tight, and everything was harder to work with because I had so little space to maneuver, especially when everything was mounted in place.
- Be patient with the wood glue: It takes time to set. Because I was messing around with the gears while the glue was still setting, I'm pretty sure I knocked the motor slightly out of place which ended up making my work so much harder to correct.

Excited for the next project!