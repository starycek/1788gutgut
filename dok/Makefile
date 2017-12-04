
NAME=dokumentace

$(NAME): $(NAME).tex
	latex $(NAME).tex
	latex $(NAME).tex
	dvips $(NAME).dvi
	ps2pdf -sPAPERSIZE=a4 $(NAME).ps