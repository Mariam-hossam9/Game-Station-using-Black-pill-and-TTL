from tkinter import *
import serial
import tkinter as tk
from tkinter import ttk
from tkinter import Canvas, Frame, Label
from tkinter import font

# --- Configure UART ---
try:
    ser = serial.Serial('COM5', 9600, timeout=1)  # ✅ Removed extra space after COM5
except Exception as e:
    print("⚠️ Error opening serial port:", e)
    ser = None

# --- Functions to send commands ---
def send_command(cmd):
    if ser and ser.is_open:
        ser.write(cmd.encode())   # send as ASCII
        print(f"📤 Sent command: {cmd}")
    else:
        print("❌ Serial port not open")

def start_math_quiz():
    send_command("M")   # 'M' = Math Quiz

def start_led_game():
    send_command("L")   # 'L' = LED Memory Game

def start_snake_game():
    send_command("S")   # 'S' = Snake Game

# --- Main Window ---
root = tk.Tk()
root.title("🎮 Game Controller")
root.geometry("520x500")
root.configure(bg="#0d0d1a")  # Darker, more dramatic background

# --- Custom Font ---
title_font = font.Font(family="Segoe UI", size=26, weight="bold")
btn_font = font.Font(family="Segoe UI", size=13, weight="bold")

# --- Animated Title ---
title = tk.Label(root, text="🎮 Game Selector", font=title_font,
                 bg="#0d0d1a", fg="#ff4757")  # Vibrant red
title.pack(pady=25)

# Glow colors for animation
glow_colors = ["#ff4757", "#ffa502", "#ff6b81", "#1e90ff", "#2ed573", "#ff7f50"]
def animate_title(i=0):
    title.config(fg=glow_colors[i])
    root.after(300, animate_title, (i+1) % len(glow_colors))
animate_title()

# --- Button Frame ---
btn_frame = Frame(root, bg="#0d0d1a")
btn_frame.pack(pady=30)

# --- Improved Button Style ---
def create_button(master, text, bg_color, command):
    return Button(
        master,
        text=text,
        bg=bg_color,
        fg="#ffffff",
        activebackground="#34495E",  # Darker shade when pressed
        activeforeground="#ffffff",
        font=("Segoe UI", 13, "bold"),
        width=22, height=2,
        bd=0,
        relief="flat",
        highlightthickness=2,
        highlightbackground="#BDC3C7",  # Subtle border
        highlightcolor="#2C3E50",
        cursor="hand2",                # Hand cursor on hover
        command=command
    )

# --- Math Quiz Button ---
btn_math = create_button(btn_frame, "🧮 Math Quiz", "#2980B9", start_math_quiz)
btn_math.pack(pady=10)

# --- LED Memory Game Button ---
btn_led = create_button(btn_frame, "💡 LED Memory Game", "#27AE60", start_led_game)
btn_led.pack(pady=10)

# --- Snake Game Button ---
btn_snake = create_button(btn_frame, "🐍 Snake Game", "#8E44AD", start_snake_game)
btn_snake.pack(pady=10)

# --- Quit Button ---
quit_btn = create_button(root, "❌ Quit", "#E74C3C", root.destroy)
quit_btn.pack(pady=12)

# --- Footer ---
footer = tk.Label(root, text="Made with ❤️",
                  font=("Segoe UI", 9, "italic"),
                  bg="#0d0d1a", fg="#FFFFFF")  
footer.pack(side="bottom", pady=10)

root.mainloop()
