# CABLESHIELDTESTINATOR

Recently a [post](https://www.instagram.com/audio.pilz/p/CvVS7SXtaue/) by AudioPilz inspired me to work on a device that non-invasively detects whether a cable is shielded or not. From an economic point of view this device makes absolutely no sense. It was a just-for-fun project to find out whether it can be done or not. Once again I learned a lot.

Cheap audio patch cables often come unshielded. That means that the second conductor (ground, the shield) is not a mesh of wires wrapped around the signal conductor (as I would expect it from cables for audio). Instead there are just two wires lying next to each other inside the coating. So I wanted to find out if it was possible to build a device that could determine whether a cable was shielded or not without cutting it. 

![cables](images/cables.png)

## The Idea

The idea was to put the cable through a coil, run signals through both conductors in an alternating way and measure the response that gets induced in the coil. 

![Block  diagram](images/blockdiagram.png)

A cable with two equal conductors (unshielded) should behave different from a cable where one conductor is wrapped around the other one (shielded). It turned out that this approach oviously was good enough to separate shielded cables from unshielded ones.

<img src="images/photo1.jpg" width="400"><img src="images/photo2.jpg" width="400">

## Circuit Diagram

The cicruit uses a TL084 as an oscillator to generate a triangular waveform at about 250 Hz. An ATMEGA328p microcontroller uses two relays to pass this signal through this or that conductor of the cable which is placed inside a coil. The signals in the cable therefore induce weak currents in the coil. The coil itself is connected to another TL084 to amplify and smooth these signals. Finally, the microcontroller reads the analog signal and evaluates it.

![Block  diagram](images/schematic.png)

The signal generator uses a pair of transistors to amplify the signal to it's maximum. Theoretically (depending on the transistors) we run up to 12V through a 100 ohms resistor and so up to 120mA through the cable. This corresponds to about 1.44 watts.

The large capacitors at the output of the signal receiver smooth out the signal very nicely for the ADC. However, the microcontoller must wait a second before measuring the voltage in order to let the signal reach it's final value. Maybe these capacitors could be reduced to a minimum which still guarantees a stable signal but reduces the time to reach it.

## Recycling

I love mixing old and new components in my creations. In this project for instance I used new-old-stock operational amplifiers from the former GDR (B084 instead of TL084) and the transistors are from this era too. The beautiful large coils are new-old-stock from ebay. The 100 ohms resistor was de-soldered from an old computer power supply. I also used recycled filament for the case.

## The Code

The microcontroller rotates through the four possible states of the two relays and measures the voltage received by the coil. Larger differences between the four options indicate a shielded cable, similar values indicate an unshielded cable.

## The Case

I designed the case myself and printed it with my own 3D printer. I used recycled filament from [Recycle Fabrik](https://recyclingfabrik.com) to reduce plastic waste.

## Contact 

If you like my work and want to contact me for hardware- or software-related projects, head over to https://seige.digital









