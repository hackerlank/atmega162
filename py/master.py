import serial
import time
import re

ser = serial.Serial('/dev/cu.usbserial', 38400, timeout=0)
#ser.write(b'AT+HELP\r\n')
#print(ser.read(102400))

def show_hex(data):
	result = ''  
	hLen = len(data)
	for i in xrange(hLen):
		hvol = ord(data[i])
		hhex = '%02x' % hvol
		result += hhex + ' '
	print 'hex:', result

def send(txt):
	#ser.write(txt)
	#ser.write(b'\r\n')
	# ser.write(txt + b'\r\n')
	ser.write(txt)
	time.sleep(0.3)
	res = ''
	print 'sent:',
	print txt
	show_hex(txt)
	s = ser.read(1024)
	while len(s) > 0:
		res += s
		time.sleep(0.3)
		s = ser.read(1024)
	print(res)

global addr_a
global addr_b
addr_a = 0xfffe
addr_b = 0xfffe

def send_a(txt):
	cmd = chr(0xfd)
	cmd += chr(len(txt))
	cmd += chr((addr_a & 0xff00) >> 8)
	cmd += chr(addr_a & 0x00ff)
	cmd += txt
	send(cmd)

def send_b(txt):
	cmd = chr(0xfd)
	cmd += chr(len(txt))
	cmd += chr((addr_b & 0xff00) >> 8)
	cmd += chr(addr_b & 0x00ff)
	cmd += txt
	send(cmd)

re_zigbee_ready = re.compile('zigbee_ready\((\w)\);')

def checkCmd(txt):
	global addr_a
	global addr_b
	match = re_zigbee_ready.match(txt)
	if match:
		if match.group(1) == 'a':
			addr_a = ord(txt[16]) << 8 | ord(txt[17])
			print('addr_a: %04x' % addr_a)
			send_a('got(a);')
		elif match.group(1) == 'b':
			addr_b = ord(txt[16]) << 8 | ord(txt[17])
			print('addr_b: %04x' % addr_b)
			send_b('got(b);')
			# time.sleep(2)
			# send_b('dis(a);')


while True:
	read = ser.read(102400)
	if (len(read) > 1):
		print(read)
	checkCmd(read)
	time.sleep(0.5)
