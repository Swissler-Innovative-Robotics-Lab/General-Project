
% === Load and Prepare RGB + HSL Data ===
M = readmatrix('color_data2.csv');  % Nx6 matrix
RGB = M(:, 1:3);                   % Nx3 matrix of R, G, B (normalized)
L = M(:, 4);                       % Lightness ∈ [0,1]
S = M(:, 5);                       % Saturation ∈ [0,1]

% === Normalize RGB (if needed) ===
if max(RGB(:)) > 1
    RGB = RGB ./ max(RGB(:));  % scale to [0,1] if raw values
end

% === Calculate Hue for Each Row ===
H = arrayfun(@(i) calcHue(RGB(i,1), RGB(i,2), RGB(i,3)), 1:size(RGB,1))';

% === Convert to 3D Cartesian for Bicone Plotting ===
theta = 2 * pi * H;
radius = S .* (1 - abs(2 .* L - 1));
x = radius .* cos(theta);
y = radius .* sin(theta);
z = L;

% === Plot: Color Each Point by Its RGB ===
figure;
scatter3(x, y, z, 60, RGB, 'filled');
xlabel('Hue X');
ylabel('Hue Y');
zlabel('Lightness');
title('3D HSL Bicone');
axis equal;
grid on;

% === Vectorized Preucil Hue Function ===
function hue = calcHue(R, G, B)
    eps = 1e-10;  % to prevent divide-by-zero
    
    if R >= G && G >= B
        hue = 60 * ((G - B) / max(R - B, eps));
    elseif G >= R && R >= B
        hue = 60 * (2 - (R - B) / max(G - B, eps));
    elseif G >= B && B >= R
        hue = 60 * (2 + (B - R) / max(G - R, eps));
    elseif B >= G && G >= R
        hue = 60 * (4 - (G - R) / max(B - R, eps));
    elseif B >= R && R >= G
        hue = 60 * (4 + (R - G) / max(B - G, eps));
    elseif R >= B && B >= G
        hue = 60 * (6 - (B - G) / max(R - G, eps));
    else
        hue = 0.0;
    end
    
    hue = mod(hue / 360.0, 1.0);  % Normalize to [0, 1]
end
