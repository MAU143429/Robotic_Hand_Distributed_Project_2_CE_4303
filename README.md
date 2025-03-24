# ✋ Robotic Hand System with Secure Distributed Processing — CE4303

## 🧠 Project Overview

This repository contains the implementation of a **distributed, secure, and hardware-integrated system** developed as part of the **Operating Systems Principles Course (CE4303)**.

Our team chose to build a **robotic hand** capable of simulating typing on a keyboard. The system includes a custom **Linux device driver**, a **distributed processing backend using OpenMPI**, and a hardware prototype with actuators simulating finger motion.

---

## 🔧 What You'll Find in This Repository

- 🖐️ **Robotic Hand Firmware and Schematics**  
  Arduino system code controlling servos for simulating keystrokes.

- 📦 **Linux Kernel Module (USB Device Driver)**  
  Written in C to allow user-space applications to interact with the robotic hand hardware.

- 🧰 **User-Space Library**  
  A `.a` library offering high-level functions (e.g., `write_word()`, `move_finger()`) to control the robotic hand via the driver.

- 🧠 **Server-Client Architecture**  
  A **distributed cluster** built with OpenMPI that:
  - Receives encrypted text from the client
  - Decrypts the text across several nodes
  - Finds the most repeated word
  - Sends it to the robotic hand to be typed out

- 🔐 **Encryption Layer**  
  All communications between nodes are encrypted for security.

---

## ⚙️ How It Works

1. The client encrypts a document and sends it to the server.
2. The server distributes the decryption and word counting across multiple nodes using OpenMPI.
3. The most repeated word is identified and passed to the library.
4. The library interacts with the custom Linux driver.
5. The robotic hand types the result on a surface (physical/digital keyboard).

---

## 💡 Technologies Used

- C (Device Driver, Server, Client, Library)
- OpenMPI (Cluster communication and parallel processing)
- Linux (Kernel module development and testing)
- Embedded system (e.g., Arduino for hardware control)
- Optional: Python for testing and visualization

---

## 📌 Notes

- The system includes **I/O management**, **device drivers**, **secure communication**, and **distributed computation**.
- All hardware-software interaction is handled via a custom kernel module and library.
- The encryption algorithm used for secure transfer is defined and implemented by the group.


