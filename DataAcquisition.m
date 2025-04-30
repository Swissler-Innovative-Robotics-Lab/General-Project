% --- Configure Serial Port ---
s = serialport("COM7", 115200);  % Replace COM3 with your port
configureTerminator(s, "LF");   % Match Arduino's println (newline)
flush(s);  % Clear the serial buffer

% --- Storage Variables ---
data = [];
disp("Reading... Press Ctrl+C to stop");

% --- Data Acquisition Loop ---
while true
    line = readline(s);  % Read one line at a time
    vals = str2double(split(line, ","));  % Split and convert

    if length(vals) == 5 && all(~isnan(vals))  % Check valid line
        data(end+1, :) = vals;
    end

end

%Column order: R, G, B, L, S
%{
filename = "color_data2.csv";
writematrix(data, filename);
disp("Data saved to " + filename);
%}


