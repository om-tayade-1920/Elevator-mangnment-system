# 🚦 Elevator Control System using AT89C51 (8051 Microcontroller)

This project simulates a multi-floor **Elevator (Lift) Control System** using the **AT89C51 microcontroller** from the 8051 family. The system supports **six floors (Ground + 5)**, displays the current floor on a **7-segment display**, and shows door status on a **16x2 LCD display**. It also features **overweight detection** for safety.

---

🎥 **Project Demo Video:**  
[Watch on YouTube](https://youtu.be/dvghVo5i9CA)

---

## 📦 Key Components

- **AT89C51 Microcontroller**
- **16x2 LCD Display** – for door status
- **7-Segment Display + 7447 BCD to 7-Segment Driver** – for floor display
- **ULN2003A Motor Driver IC** – to control the motor
- **Push Buttons** – for floor selection
- **Overweight Detection Key**
- **Power Supply Unit**

---

## 🛠️ Software Used

- **Keil µVision IDE** – for Embedded C programming
- **Proteus Design Suite** – for circuit simulation and testing

---

## ⚙️ Features

- Floor selection via push buttons (Ground to 5th floor)
- LCD shows:
  - Door status: “Door Open” / “Door Closed”
  - Floor number
  - Overload alert
- 7-segment display shows current floor number
- Elevator movement logic (Up/Down) handled via step sequences
- Overweight condition handling using a safety switch
- Simulated motor control via ULN2003A

---

## 🧠 How It Works

1. User presses a floor button.
2. Microcontroller calculates direction and moves accordingly.
3. During travel, a message like “Moving Up” or “Moving Down” is shown on the LCD.
4. On arrival, LCD shows floor number and door opens temporarily.
5. Overweight input disables movement and shows a warning.

---

## 🧾 Code Summary (Embedded C)

- LCD interfacing using 8-bit mode on `P1`
- Stepper motor control using ULN2003A via `P3`
- Overload key connected to `P3.4`
- Floor input via `P0`
- Display logic using `P2` and 7-segment BCD decoder
- Movement delays simulate real-world timing

---




