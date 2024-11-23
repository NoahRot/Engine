#version 330 core
out vec4 FragColor;

uniform vec3 u_cam_position;

vec4 step(vec4 color) {
    vec4 new;
    new.r = color.b;
    new.g = color.r;
    new.b = color.g;
    return new;
}

void main()
{
    int width = 2;              // Width of the elements
    int cote = 40;              // Distance between 2 adjacent points
    int center_point_rad = 20;  // Centroid point radius

    vec2 world_position = vec2(gl_FragCoord.x - u_cam_position.x, gl_FragCoord.y - u_cam_position.y);
    vec4 color_back = vec4(0.05, 0.1, 0.2, 1.0);        // Background color
    vec4 color_secondary = vec4(0.5, 0.4, 0.15, 1.0);   // Color of the points
    vec4 color_axis = vec4(0.6, 0.2, 0.1, 1.0);         // Color of the axis

    float mod_x = mod(world_position.x, cote);          // Position relative to the current cell
    float mod_y = mod(world_position.y, cote);          // Position relative to the current cell
    
    // Color of the background and the cells
    if (mod_x < width && mod_y < width) {
        FragColor = vec4(color_secondary);
    }else{
        FragColor = vec4(color_back);
    }

    // Color of the axis and of the centroid point
    if (dot(world_position, world_position) < center_point_rad) {
        FragColor = color_axis;
    }else if (world_position.x > 0 && world_position.x < cote && abs(world_position.y) < width) {
        FragColor = step(color_axis);
    }else if (world_position.y > 0 && world_position.y < cote && abs(world_position.x) < width) {
        FragColor = step(step(color_axis));
    }
}