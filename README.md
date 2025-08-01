# Clap Detection Rhythm Tracker - Arduino Project

This project is an Arduino-based system that allows users to create and save custom rhythmic patterns using clap detection. The system captures claps, stores them as rhythms, and can play them back by blinking LEDs and emitting sound tones.

## Features

- **Clap Detection:** Uses a sound sensor to detect claps.
- **Rhythm Storage:** Save and load multiple rhythmic patterns in EEPROM.
- **Hardware Support:** Configurable to use multiple buttons, LEDs, and sound output.
- **User Interaction:**
  - **Add Claps:** Add claps to a rhythm pattern by detecting sound.
  - **Play Rhythm:** Play saved rhythm patterns back using LEDs and sound output.
  - **Switch Rhythms:** Cycle through different rhythm patterns.
  - **Toggle Clap Recording:** Enable or disable adding claps to the rhythm.
  
## Components Required

- **Arduino Board** (e.g., Arduino Uno)
- **Sound Sensor**
- **3 Push Buttons**
- **3 LEDs**
- **Buzzer**
- **Wires and Breadboard**
- **Resistors** (for LEDs and buttons)

## Pin Configuration

- **Buttons:**
  - Pin 2, 3, 4 (for interaction)
  
- **LEDs:**
  - Pin 7, 8, 13 (for visual feedback)

- **Buzzer:**
  - Pin 12 (for audio feedback)
  
- **Sensor Pin:**
  - Pin A0 (for the sound sensor)

## How It Works

1. **Clap Detection:**
   The system uses a sound sensor to detect loud sounds (claps). When the sensor value exceeds the defined sensitivity, it adds a clap to the current rhythm.

2. **Rhythm Creation:**
   Multiple rhythms can be created by adding claps. Each rhythm can have up to 8 claps. Rhythms are saved in the **EEPROM** of the Arduino.

3. **Playback:**
   Saved rhythms can be played back, with LEDs blinking in sync with the rhythm and a buzzer emitting sound.

4. **User Control:**
   - **Button 1:** Switch between rhythms.
   - **Button 2:** Toggle the ability to add claps to the rhythm.
   - **Button 3:** Play the current rhythm.

## Functions

- **addClapToRhythm()**: Adds a detected clap to the current rhythm.
- **playRhythm()**: Plays the rhythm using LEDs and the buzzer.
- **switchRhythm()**: Switches between rhythms.
- **saveRhythmsToEEPROM()**: Saves all rhythms to **EEPROM**.
- **loadRhythmsFromEEPROM()**: Loads rhythms from **EEPROM** at startup.
- **checkSavedRhythms()**: Checks if the current rhythm matches any saved rhythm and provides feedback.
- **resetRhythms()**: Resets all rhythms to empty (currently unused).
  
## How to Set Up

1. **Hardware Setup:**
   - Connect the **sound sensor** to analog pin **A0**.
   - Connect the **buttons** to pins **2, 3, and 4**.
   - Connect the **LEDs** to pins **7, 8, and 13**.
   - Connect the **buzzer** to pin **12**.

2. **Upload the Code:**
   - Open the Arduino IDE.
   - Copy and paste the code from this repository.
   - Select your **Arduino board** and **port**.
   - Click **Upload**.

## Usage

- **Add Claps:** Make a loud noise or clap to add to the rhythm.
- **Cycle Through Rhythms:** Press Button 1 to switch between different rhythms.
- **Toggle Clap Recording:** Press Button 2 to enable or disable adding claps to the rhythm.
- **Play Rhythm:** Press Button 3 to play the currently selected rhythm.

## Future Improvements

- Add a **reset functionality** to clear saved rhythms.
- Improve **clap detection** with better sensitivity tuning.
- Introduce more complex rhythm playback (e.g., adjustable speed or delay between claps).


## Contributing

Feel free to fork this repository and submit pull requests with improvements, bug fixes, or new features.

## Contact

For any questions, please feel free to reach out via the GitHub issues page or email at asher.iz.mad@gmail.com .
