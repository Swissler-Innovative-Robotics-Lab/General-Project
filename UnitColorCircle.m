% Number of hue steps (e.g., 360 for 1° resolution)
n = 88;

% Hue values from 0 to 1
huetest = linspace(0, 1, n);

% Convert hue to angle in radians
theta2 = 2 * pi * H;

% Saturation = 1 ⇒ radius = 1
radius = 1;

% Cartesian coordinates
x = radius * cos(theta2);
y = radius * sin(theta2);

% Plot
figure;
scatter(x, y, 30, RGB, 'filled');  % HSV colormap for rainbow hues
axis equal;
xlabel('Hue X');
ylabel('Hue Y');
title('2D Hue Circle (Saturation = 1)');
grid on;
