NAME	=	tagascii

RM		=	rm -rf

DEBUG	=	1

EXTENSION	=	.cpp

SRC		=	$(wildcard $(addprefix renderer/sources/, *)$(EXTENSION))

NOM		=	$(basename $(notdir $(SRC)))

OBJ		=	$(addprefix renderer/objects/, $(addsuffix .o, $(NOM)))

ifeq ($(DEBUG), 1)
  CXXFLAGS	+=	-W -Wall -Wextra -pedantic -ansi
endif

CXXFLAGS	+=	-Irenderer/includes/

all		:	obj $(NAME) clean

obj		:
			mkdir renderer/objects

$(NAME)	:	$(OBJ)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

renderer/objects/%.o	:	renderer/sources/%$(EXTENSION)
			$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

install	:	all
			@sudo install -v -m 755 $(NAME) /usr/bin/

clean	:
			$(RM) $(OBJ) renderer/objects

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re obj
