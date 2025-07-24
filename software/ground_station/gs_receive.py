import serial
import matplotlib.pyplot as plt

def main():
    port = "/dev/ttyUSB0"
    baud = 115200
    ser = serial.Serial(port, baud, timeout=1)
    uv_vals, ir_vals = [], []

    plt.ion()
    fig, ax = plt.subplots()
    line_uv, = ax.plot([], [], label='UV')
    line_ir, = ax.plot([], [], label='IR')
    ax.legend()

    while True:
        line = ser.readline().decode().strip()
        if not line: continue
        # Expect: UV:xx.xx IR:yyyy
        try:
            parts = line.split()
            uv = float(parts[0].split(':')[1])
            ir = int(parts[1].split(':')[1])
            uv_vals.append(uv)
            ir_vals.append(ir)
            line_uv.set_data(range(len(uv_vals)), uv_vals)
            line_ir.set_data(range(len(ir_vals)), ir_vals)
            ax.relim(); ax.autoscale_view()
            plt.pause(0.01)
        except:
            pass

if __name__ == "__main__":
    main()
