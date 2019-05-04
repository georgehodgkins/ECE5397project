clclc
clear
close all
load BaseData.mat
%data dump
fprintf('3DES, CBC, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_3DES(:,1)), min(CBC_3DES(:,1)), max(CBC_3DES(:,1)), std(CBC_3DES(:,1)));
fprintf('\n3DES, CBC, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_3DES(:,2)), min(CBC_3DES(:,2)), max(CBC_3DES(:,2)), std(CBC_3DES(:,2)));
fprintf('\n3DES, OFB, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_3DES(:,1)), min(OFB_3DES(:,1)), max(OFB_3DES(:,1)), std(OFB_3DES(:,1)));
fprintf('\n3DES, OFB, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_3DES(:,2)), min(OFB_3DES(:,2)), max(OFB_3DES(:,2)), std(OFB_3DES(:,2)));
fprintf('\n\nAES-128, CBC, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES128(:,1)), min(CBC_AES128(:,1)), max(CBC_AES128(:,1)), std(CBC_AES128(:,1)));
fprintf('\nAES-128, CBC, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES128(:,2)), min(CBC_AES128(:,2)), max(CBC_AES128(:,2)), std(CBC_AES128(:,2)));
fprintf('\nAES-128, OFB, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES128(:,1)), min(OFB_AES128(:,1)), max(OFB_AES128(:,1)), std(OFB_AES128(:,1)));
fprintf('\nAES-128, OFB, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES128(:,2)), min(OFB_AES128(:,2)), max(OFB_AES128(:,2)), std(OFB_AES128(:,2)));
fprintf('\n\nAES-192, CBC, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES192(:,1)), min(CBC_AES192(:,1)), max(CBC_AES192(:,1)), std(CBC_AES192(:,1)));
fprintf('\nAES-192, CBC, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES192(:,2)), min(CBC_AES192(:,2)), max(CBC_AES192(:,2)), std(CBC_AES192(:,2)));
fprintf('\nAES-192, OFB, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES192(:,1)), min(OFB_AES192(:,1)), max(OFB_AES192(:,1)), std(OFB_AES192(:,1)));
fprintf('\nAES-192, OFB, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES192(:,2)), min(OFB_AES192(:,2)), max(OFB_AES192(:,2)), std(OFB_AES192(:,2)));
fprintf('\n\nAES-256, CBC, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES256(:,1)), min(CBC_AES256(:,1)), max(CBC_AES256(:,1)), std(CBC_AES256(:,1)));
fprintf('\nAES-256, CBC, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(CBC_AES256(:,2)), min(CBC_AES256(:,2)), max(CBC_AES256(:,2)), std(CBC_AES256(:,2)));
fprintf('\nAES-256, OFB, Encrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES256(:,1)), min(OFB_AES256(:,1)), max(OFB_AES256(:,1)), std(OFB_AES256(:,1)));
fprintf('\nAES-256, OFB, Decrypting: Mean: %0.2f Min: %d Max: %d Sigma: %0.2f', mean(OFB_AES256(:,2)), min(OFB_AES256(:,2)), max(OFB_AES256(:,2)), std(OFB_AES256(:,2)));

%plotting
CBC_3DES_scale = my_scale(CBC_3DES(:,1));
OFB_3DES_scale = my_scale(OFB_3DES(:,1));
CBC_3DES_Dscale = my_scale(CBC_3DES(:,2));
OFB_3DES_Dscale = my_scale(OFB_3DES(:,2));
CBC_AES256_scale = my_scale(CBC_AES256(:,1));
CBC_AES256_Dscale = my_scale(CBC_AES256(:,2));
CBC_AES192_scale = my_scale(CBC_AES192(:,1));
CBC_AES128_scale = my_scale(CBC_AES128(:,1));
OFB_AES256_scale = my_scale(OFB_AES256(:,1));
OFB_AES256_Dscale = my_scale(OFB_AES256(:,2));
figure(1);
hold on;
axis([0 256 -Inf Inf]);
xticks([0:64:256]);
plot(1:256, CBC_3DES_scale(:,2)/1000, '-r');
plot(1:256, CBC_3DES_Dscale(:,2)/1000, '-g');
plot(1:256, CBC_AES256_scale(:,2)/1000, '-b');
plot(1:256, CBC_AES256_Dscale(:,2)/1000, '-m');
title({'AES-256 and 3DES encryption and decryption times using CBC','Averages for clusters of 32 iterations'});
xlabel('Iteration cluster');
ylabel('Cluster average encryption time [ms]');
legend('3DES encryption', '3DES decryption', 'AES-256 encryption', 'AES-256 decryption');
figure(2);
hold on;
axis([0 256 -Inf Inf]);
xticks([0:64:256]);
plot(1:256, OFB_3DES_scale(:,2)/1000, '-r');
plot(1:256, OFB_3DES_Dscale(:,2)/1000, '-g');
plot(1:256, OFB_AES256_scale(:,2)/1000, '-b');
plot(1:256, OFB_AES256_Dscale(:,2)/1000, '-m');
title({'AES-256 and 3DES encryption and decryption times using OFB','Averages for clusters of 32 iterations'});
xlabel('Iteration cluster');
ylabel('Cluster average encryption time [ms]');
legend('3DES encryption', '3DES decryption', 'AES-256 encryption', 'AES-256 decryption');
figure(3);
hold on;
axis([0 256 -Inf Inf]);
xticks([0:64:256]);
plot(1:256, CBC_AES256_scale(:,2)/1000, '-b');
plot(1:256, CBC_AES192_scale(:,2)/1000, '-g');
plot(1:256, CBC_AES128_scale(:,2)/1000, '-m');
title({'AES encryption times using CBC for varying key sizes', 'Averages for clusters of 32 iterations'});
xlabel('Iteration cluster');
ylabel('Cluster average encryption time [ms]');
legend('AES-256', 'AES-192', 'AES-128')

%-----locals-----
function [scalemat] = my_scale(selmat)
    scalemin = zeros(256,1);
    scaleavg = zeros(256,1);
    scalemax = zeros(256,1);
    for ii = 1:256
        scalemin(ii) = min(selmat(((ii-1)*32+1):(ii*32)));
        scaleavg(ii) = mean(selmat(((ii-1)*32+1):(ii*32)));
        scalemax(ii) = max(selmat(((ii-1)*32+1):(ii*32)));
    end
    scalemat = [scalemin, scaleavg, scalemax];
end
