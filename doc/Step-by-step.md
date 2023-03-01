Step-by-step instruction
===
I suppose, you have bought all needed stuff and downloaded all needed files from the project at this moment, isn't it? If no - please read the [manual](README.md) again more carefully... :)

3D prining
---

So first step is: to 3D-print all parts of the SmartFilamentSensor. I  printed these parts by 0.4 mm nozzle:

![Sensor body](img/101.SensorBody.png)
![Sensor Wheel Support](img/103.SensorWheelSupport.png)
![Engine Sensor Body](img/104.EngineSensorBody.png)

and these parts were printed by 0.2 mm nozzle for greater accuracy: 

![Engine Shaft Wheel](img/105.EngineShaftWheel.png)
![Sensor Wheel](img/102.SensorWheel.png)

Assembling parts
---

Cut by scissors a rubber ring from latex medical gloves:

![rubber ring](img/106.RubberRing.png)

Stretch the rubber ring over the highlighted surface of sensor wheel:

![highlighted surface](img/107.RubberRingOnAWheel.png)

this is necessary to prevent filament slippage and better friction.

Put a bearing on the filament wheel. I also put a drop of superglue here, just in case:

![Wheel And Bearing](img/108.WheelAndBearing.png)

Put the bearing into the wheel suport:

![Wheel And Support](img/109.WheelAndSupport.png)

Put one of sensors into main body:

![Sensor And Main Body](img/110.SensorAndBase.png)

Put a wheel with support into main body:

![Sensor And Main Body](img/111.SupportAndBase.png)

Connect wheel support and main body via rubber ring and wires... well, I don't know how I may draw it, so there is a photo of my sensor:

![Sensor And Main Body With Rubber](img/112.SupportAndBaseRubber.png)

As you can see, the rubber is stretched and fixed by twisted wires on the support and the body through the holes. Of course, you may use a spring if you have appropriate size, but I don't have one, so  I use a rubber ring and disposable packing wire (peeled of any plastic sheath).


Put second movement sensor on the engine body. You may use a drop of thermoglue or super-glue for this:

![Sensor And Engine Body](img/113.SensorAndEngineBody.png)

Soldering
---
Well, frankly speaking, soldering is optional and you may use wires with connectors, but from my point of view, it may produce a lot of issues with connections and as result, incorrect and unstable behaviour of SmartSensor... so I'd like to prefer soldering.

Connect all elements regarding to the scheme:

![Sensor And Engine Body](img/114.SolderingScheme.png)

Flashing firmware
---
Connect RP2040Zero to your PC via USB cable. Press 'RESET' button on the plate, don't release the button and press 'BOOT' button so you should have two buttons pressed. Release 'RESET' button and next release 'BOOT' button. f you did everything correctly, your RP2040Zero will be visible for your PC as an USB flash drive. Copy firmware bin-file to the 'usb stick'. After it, the drive will be disconnected and firmware successfully flashed to the plate.

Final steps
---
On the final step, need to put Engine wheel on a motor shaft and put 'engine sensor body' with a sensor to body of extruder using few drop of superglue. It should looks like:

![Assembly Engine Part](img/115.AssemblyEnginePart.png)
