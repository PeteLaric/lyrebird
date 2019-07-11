function [ number ] = note_to_number( note )
%NOTE_TO_NUMBER Converts a note character to an integer.
%   Notes are 'A', 'C', 'E', and '.'.  Numbers are 1, 2, 3, 0 respectively.

number = 0;

if (note == 'A')
    
    number = 1;
    
elseif (note == 'C')
    
    number = 2;
    
elseif (note == 'E')
    
    number = 3;
    
end

end

