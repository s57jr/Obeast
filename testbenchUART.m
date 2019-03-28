if ~isempty(instrfind)
     fclose(instrfind);
     delete(instrfind);
end
    
testbench = serial('/dev/tty.usbserial')  %,'BaudRate',9600); 

fopen(testbench); 

uint8 sensorNbr; 
uint8 sensorData0; 
uint8 sensorData1; 
uint8 byteS;
uint8 byteT;

byteS = 115; 
byteT = 116; 

for i=0:1:39
    sensorNbr = i
    sensorData0 = 1000+i; 
    sensorData1 = 2000+i; 
    message = [byteS byteT sensorNbr sensorData0 sensorData1]; 
%    fprintf(testbench,message); 
end 

fclose(testbench)