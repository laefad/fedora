from asyncio.log import logger
from sly import Lexer, Parser
import json
import logging

"""
EBNF of the syntax that this parser reads:

;; s-symbol         ::= "[^()\[\]= \n\t\r]+[^()\[\]=" \n\t\r]*" .
;; s-name           ::= <s-symbol>+ .
;; s-float          ::= "[-+]?[0-9]+.[0-9]+(E[-+]?[0-9]+)?" .
"""

"""
EXAMPLE:
(
    (let main (arg1, arg2) () )
)
"""

class Lex:
    """The class of the token. When the parser recognizes something, it writes it to the instance of this class.
 In data, it is always either NAME or NUMBER."""
    def __init__(self, data):
        self.data = data
        self.master = None
        self.slaves = []

    def __str__(self):
        return str(self.data)

class S_SYMBOL(Lex):
    pass

class S_NAME(Lex):
    pass

class FedoraLexer(Lexer):
    """Lexer. Splits the input string into tokens"""
    tokens = {NAME, NUMBER, LPAREN, RPAREN}
    ignore = ' \t'

    # Tokens
    NAME = r'[^()\[\]= \n\t\r]+[^()\[\]=" \n\t\r]*'   
    NUMBER = r'\d+'

    # Special symbols
    LPAREN = r'\('
    RPAREN = r'\)'

    # Ignored pattern
    ignore_newline = r'\n+'
    ignore_comments = r'\/\*.*\*\/'    # Ignore comments

    def error(self, t):
        self.index += 1


class FedoraParser(Parser):
    tokens = FedoraLexer.tokens

    precedence = (
        ('left', NAME),
    )

    def __init__(self):
        self.root = None
        self.errors = False
        self.is_comm = False

    def error(self, token):
        if not self.errors:
            print('Syntax error!!')
        self.errors = True

    @_('NAME')
    def word(self, p):
        """
        Turns every sequence of characters into a word
        """
        logger.debug('s-name: '+str(p[0])+'to word')
        return p[0]

    # @_('SYMBOL SYMBOL')
    # def expr(self, p):
    #     name = S_NAME(p[0]+p[1])
    #     print('s-name: '+str(a.data))
    #     return a

if __name__ == '__main__':
    """The main function of the program.
 Reads the information from the file and translates the tree of paired objects first to serializable, and then to Json"""
    lexer = FedoraLexer()
    parser = FedoraParser()
    
    logging.basicConfig(level=logging.DEBUG)

    text = 'programs/new_syntax.fe'
    if text:
        
        try:
            with open(text, 'r') as content_file:
                content = content_file.read()
                parser.parse(lexer.tokenize(content))
        except FileNotFoundError:
            print('File does not exist!')
        
        # if not parser.errors:
        #     root = parser.root
        #     serializable = root.get_serializable()
        #     print('Output JSON:')
        #     print(json.dumps(serializable, indent=1, ensure_ascii=False))
        # else:
        #     print('No output JSON due to syntax error.')