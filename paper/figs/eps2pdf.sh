mv $1 temp.eps
epstool --bbox --copy temp.eps --output $1
epstopdf --nocompress $1
