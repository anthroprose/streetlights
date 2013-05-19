import json
import sys
import serial
import time

from pprint import pprint
from flask import Flask
from flask import render_template
from flask import request

ttyusb = '/dev/ttyUSB1'

def set_colors(r,g,b):

    try:
        
        pprint('0,' + str(r) + ',' + str(g) + ',' + str(b))
        ser.write('0,' + str(r) + ',' + str(g) + ',' + str(b) + "\n")
            
    except Exception as e:
        pprint("Unhandled Exception: " + e.reason)
        
    except:
        pprint("Unhandled Exception: " + str(sys.exc_info()))

    return json.dumps(r,g,b)

def set_color(i,r,g,b):

    try:
        
        pprint(str(i) + ',' + str(r) + ',' + str(g) + ',' + str(b))
        ser.write(str(i) + ',' + str(r) + ',' + str(g) + ',' + str(b) + "\n")
            
    except Exception as e:
        pprint("Unhandled Exception: " + e.reason)
        
    except:
        pprint("Unhandled Exception: " + str(sys.exc_info()))

    return json.dumps(i,r,g,b)

if __name__ == "__main__":
    
    ser = serial.Serial(ttyusb, 57600, timeout=2)
    
    app = Flask(__name__)
    app.config.from_object(__name__)
    
    @app.route('/colors/')
    def set_color_handler():
        return set_colors(request.args.get('r', ''),request.args.get('g', ''),request.args.get('b', ''))
    
    @app.route('/color/')
    def set_color_handler():
        return set_color(request.args.get('i', ''), request.args.get('r', ''),request.args.get('g', ''),request.args.get('b', ''))
    
    @app.route('/help')
    def help_handler():
        return render_template('help.html')
    
    @app.route('/')
    def index_handler():
        return render_template('index.html')

    app.run(host='0.0.0.0',port=80)
