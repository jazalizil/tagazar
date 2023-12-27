NAME	=	jazaoazar

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

all		:	obj $(NAME)

obj		:
			mkdir objects

$(NAME)	:	$(OBJ)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

objects/%.o	:	sources/%$(EXTENSION)
			$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

install	:	all
			@sudo install -v -m 755 $(NAME) /usr/local/bin

clean	:
			$(RM) $(OBJ) objects

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re obj
