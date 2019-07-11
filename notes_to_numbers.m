function [ num_vector ] = notes_to_numbers( char_vector )
%NOTES_TO_NUMBERS Converts a character vector of notes to a numeric vector.
%   Notes are 'A', 'C', 'E', and '.'.  Numbers are 1, 2, 3, 0 respectively.

[m, n] = size(char_vector);

for i=1:n
    
    c = char_vector(i);
    num = note_to_number(c);
    
    if exist('num_vector')
        num_vector = [num_vector num];
    else
        num_vector = num;
    end
    
end

end

