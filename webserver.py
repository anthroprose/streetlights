import json
import sys
import serial
import time

from pprint import pprint
from flask import Flask
from flask import render_template
from flask import request

ttyusb = '/dev/ttyUSB0'

def set_colors(jcolors):

    try:
        
        colors = json.loads(str(jcolors))
        
        i=0
        for c in colors:
            i=i+1
            pprint(str(i) + ',' + str(c[0]) + ',' + str(c[1]) + ',' + str(c[2]))
            ser.write(str(i) + ',' + str(c[0]) + ',' + str(c[1]) + ',' + str(c[2]) + "\n")
            
    except Exception as e:
        pprint("Unhandled Exception: " + e.reason)
        
    except:
        pprint("Unhandled Exception: " + str(sys.exc_info()))
    
    time.sleep(.5)
    return json.dumps(jcolors)

if __name__ == "__main__":
    
    ser = serial.Serial(ttyusb, 57600, timeout=2)
    
    app = Flask(__name__)
    app.config.from_object(__name__)
    
    @app.route('/colors/')
    def set_color_handler():
        colors = request.args.get('colors', '')
        return set_colors(colors)
    
    @app.route('/help')
    def help_handler():
        return render_template('help.html')
    
    @app.route('/')
    def index_handler():
        return render_template('index.html')

    app.run(host='0.0.0.0',port=80)
