function vector_plot(varargin)
switch length(varargin)
    case 1
        t_data = varargin(1);
        save_function = false;
    case 2
        t_data = varargin(1);
        p_data = varargin(2);
        save_function = false;
    case 3
        t_data = varargin{1};
        p_data = varargin{2};
        png_name = cell2mat(varargin(3));
        save_function = true;
end 
%koordinttes of path 
x = t_data.x;
y = t_data.y;
z = t_data.z;

%koordinttes of vectors 
 u = p_data.ax;
 v = p_data.ay;
 w = p_data.az;

% g_x = gradient(x);
% g_y = gradient(y);
% g_z = gradient(z);


% straching the vector, sacele = 0 -> autoscale 
scale = 0.2;
f1 = figure('name','vector_plot');
% 
% from = 1;
% step = 35;
% to = length(x);
% number_of_point = [from:step:to];
% 
% x = x(number_of_point);
% y = y(number_of_point);
% z = z(number_of_point);
% 
% u = u(number_of_point);
% v = v(number_of_point);
% w = w(number_of_point);

% g_x = g_x(number_of_point);
% g_y = g_y(number_of_point);
% g_z = g_z(number_of_point);

quiver3(x,y,z,v,u,w,scale);
hold on
%quiver3(x,y,z,g_x,g_y,g_z,scale);
plot3(x,y,z);
line( x,y,z, 'Marker', 'o', ...
    'Color', 'b', 'MarkerFaceColor', 'b', 'MarkerSize', 5 );
line(x(end),y(end),z(end), 'Marker', 's', ...
    'Color', 'b', 'MarkerFaceColor', 'b', 'MarkerSize', 8);
hold off

title('Trajektória (ECEF)')
xlabel('x [m]')
ylabel('y [m]')
zlabel('z [m]')



% 
%     %set the axes of limits 
%     r = 0.15;
%     delta_x = max(x)-min(x);
%     delta_x= delta_x*r;
%     
%     delta_y = max(y)-min(y);
%     delta_y= delta_y*r;
%     
%     delta_z = max(u)-min(u);
%     delta_z= delta_z*r;
%     
%     distance = [delta_x, delta_y, delta_z]
%     
%     %steady state case || total distance < 1mm
%     if sum(distance) <= 1*10e-3    
%         xlim([ 0 1]);
%         ylim([ 0 1]);
%         zlim([ 0 1]);
%     end
%     
%     %total disctance > 1mm 
%     if sum(distance) >= 1*10e-3  
%         xlim([min(x)-delta_x max(x)+delta_x]);
%         ylim([min(y)-delta_y max(y)+delta_y]);
%         zlim([min(z)-delta_z max(z)+delta_z]);
%         
%         xlim([min(x)-max_delta max(x)+max_delta]);
%         ylim([min(y)-max_delta max(y)+max_delta]);
%         zlim([min(z)-max_delta max(z)+max_delta]);
%     end
%     view([109 30])
%     

if save_function == true
    %png_name = cell2mat(varargin(2));
    folder_of_save = '\result\';
    save_name_with_path = [pwd folder_of_save png_name];
    saveas(f1,[save_name_with_path '.png'])
    saveas(f1,[save_name_with_path,'.fig'])
end



end


