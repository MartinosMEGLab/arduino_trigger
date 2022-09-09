

% arduino = serialport("/dev/tty.usbmodem1411201",9600);
tic
write(arduino,"100 200","char")
toc,
write(arduino,"0 0","char")
toc,

tic,
% read(arduino,200,"char")
toc

