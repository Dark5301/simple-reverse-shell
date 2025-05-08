# simple-reverse-shell
# 🔧 Reverse Shell Client in C

## 📌 Overview

This project demonstrates a **reverse shell client** written in C. The client connects back to a listener (attacker’s machine) and executes system commands received from it. The tool was created **solely for educational and ethical hacking practice**, specifically to understand socket programming and reverse shell behavior.

The server side was tested using **Netcat**, and the client successfully executes commands and returns their output over the socket.

---

## 🧠 Learning Objectives

- Practice low-level socket programming in C
- Understand how reverse shells function
- Implement basic remote code execution through sockets
- Explore common red-team and penetration testing techniques

---

## 🖥️ How It Works

1. The client creates a TCP connection to a predefined IP and port.
2. It waits for incoming command strings from the listener.
3. Commands are executed using `popen()` on the target system.
4. The result of each command is sent back through the socket.

---

## 📸 Screenshot (Demo)

Below is a test session where the reverse shell successfully:
- Connects to the attacker's machine (via Netcat)
- Executes commands such as `whoami`, `id`, and `ls`
- Writes command output to a text file on the client side

![reverse shell demo]
![reverse_shell](https://github.com/user-attachments/assets/c629b05f-8c1e-4659-a2f7-104f564509de)


---

## 🧪 Testing Setup

### 🖥️ Listener (attacker machine):
```bash
sudo nc -l 8000
