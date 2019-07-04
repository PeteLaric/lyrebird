function [ pitch ] = select_pitch( chord_component, current_chord )
%SELECT_PITCH Inputs a chord component (0 to 3) and outputs a pitch (-1 to 7).
%   -1 is a special designation for "silence", i.e. a rest.

pitch = current_chord;

if chord_component == 0
    
    pitch = current_chord + 0; %redundant, but for clarity
    
elseif chord_component == 1
    
    pitch = current_chord + 3; %3=minor_third, 4=major_third
    
elseif chord_component == 2
    
    pitch = current_chord + 7; %7=fifth
    
else
    
    pitch = -1; %silence
    
end

end

