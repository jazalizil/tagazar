NAME	=	tagazar

RM		=	rm -rf

DEBUG	=	1

EXTENSION	=	.cpp

SRC		=	$(wildcard $(addprefix sources/, *)$(EXTENSION))

NOM		=	$(basename $(notdir $(SRC)))

OBJ		=	$(addprefix objects/, $(addsuffix .o, $(NOM)))

ifeq ($(DEBUG), 1)
  CXXFLAGS	+=	-W -Wall -Wextra -pedantic -ansi
endif

CXXFLAGS	+=	-Iincludes/

all		:	link obj $(NAME)

obj		:
			mkdir objects

crawler:
			@cd crawler; \
			read -p "Set word:[Tag] " WORD; \
			echo $$WORD; \
			pwd; \
			scrapy crawl Tag -a word=$$WORD; \
			cd ..;

link: 
			@ln -sn ../crawler/tags.h includes/tags.h


$(NAME)	:	$(OBJ)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

objects/%.o	:	sources/%$(EXTENSION)
			$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

install-python:
			@pyenv install -s
			@pip install -r requirements.txt
			@playwright install

install	:	install-python crawler all
			@sudo install -v -m 755 $(NAME) /usr/local/bin

clean	:
			$(RM) $(OBJ) objects includes/tags.h

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re obj link crawler install-python
