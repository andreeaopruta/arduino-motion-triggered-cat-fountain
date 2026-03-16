# Smart Motion-Activated Cat Water Fountain

## Project Overview
This is a personal project I built to upgrade my cat's water fountain. The original fountain ran continuously (24/7), which was inefficient, consumed unnecessary power, and put continuous wear on the AC water pump. I modified the system to turn on automatically only when the cat approaches, using a PIR motion sensor, an Arduino-compatible microcontroller, and a custom power-routing circuit.

## Engineering Highlights
What makes this project interesting from a hardware perspective is the single-power-supply design. The original water pump requires a **12V AC** power source. 
Instead of using two separate wall adapters (one for the AC pump and one for the 5V DC microcontroller), I engineered a single-cable solution:
* **Handling the AC Load:** The 12V AC line is routed through a 1-channel relay (with optocoupler isolation) to switch the pump safely.
* **AC to DC Conversion:** I tapped into the 12V AC line and built a custom full-wave bridge rectifier using four 1N4007 diodes. 
* **Voltage Rating Calculation:** The 12V AC adapter outputs an RMS voltage. The peak voltage is actually higher ($V_{peak} = 12V \cdot \sqrt{2} \approx 16.97V$). To ensure long-term stability and avoid capacitor blowout, I specifically avoided 16V capacitors and implemented a capacitor bank using three 100uF/50V electrolytic capacitors in parallel for smoothing.
* **Voltage Regulation:** An LM2596 buck converter module steps down the smoothed DC voltage to a stable 5V DC for the logic board and the PIR sensor.

## Hardware Components
* 1x Original Pet Fountain with 12V AC Pump
* 1x 12V AC Wall Adapter (250mA)
* 1x Jade N1 Board (Arduino Nano compatible)
* 1x HC-SR501 PIR Motion Sensor
* 1x 1-Channel 5V Relay Module (with Optocoupler)
* 1x LM2596 Step-Down Buck Converter
* 4x 1N4007 Rectifier Diodes
* 3x 100uF 50V Electrolytic Capacitors

## Pin Connections
* **PIR Sensor:** `VCC` -> 5V | `GND` -> GND | `OUT` -> D2
* **Relay Module:** `DC+` -> 5V | `DC-` -> GND | `IN` -> D3 | `COM` -> AC input wire | `NO` -> Pump wire

## Software Logic
The logic uses `millis()` for non-blocking delays. When the PIR sensor detects motion, the microcontroller triggers the relay to turn the pump on. Once the cat leaves the sensor's range, the code keeps the pump running for an extra 30 seconds to ensure the cat has finished drinking, then shuts it off gently. 

https://github.com/user-attachments/assets/5067a037-6a1f-437c-9dc9-cef8a7bfa84c
