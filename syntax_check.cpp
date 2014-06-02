#include "headers/syntax_check.h"


Syntax::Syntax(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    SyntaxRule rule;


//comments
    singleLineCommentFormat.setForeground(QColor("#888"));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    SyntaxRules.append(rule);

    multiLineCommentFormat.setForeground(QColor("#888"));

    commentStart = QRegExp("/\\*");
    commentEnd = QRegExp("\\*/");
//strings
    quotationFormat.setForeground(QColor("#ffcf0f"));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    SyntaxRules.append(rule);

    quotPreFormat.setForeground(QColor("#ffcf0f"));
    rule.pattern = QRegExp("<.*>");
    rule.format = quotPreFormat;
    SyntaxRules.append(rule);

    quotBinFormat.setForeground(QColor("#ffcf0f"));
    rule.pattern = QRegExp("\'.*\'");
    rule.format = quotBinFormat;
    SyntaxRules.append(rule);
//functions+Qt_classes
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor("#00aeff"));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    SyntaxRules.append(rule);

    classFormat.setForeground(QColor("#49e33e"));
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    SyntaxRules.append(rule);
//preprocessor
    preProcessorFormat.setForeground(QColor("#ff8a00"));
    rule.pattern = QRegExp("^#[A-Za-z0-9_]+(\\s||\\n)");
    rule.format = preProcessorFormat;
    SyntaxRules.append(rule);
//dictionary
    keywordFormat.setForeground(QColor("#f3390e"));
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bif\\b"
                    << "\\belse\\b" << "\\bfor\\b";
    foreach (const QString &pattern, keywordPatterns){
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        SyntaxRules.append(rule);
    }
}

void Syntax::highlightBlock(const QString &text){
    foreach (const SyntaxRule &rule, SyntaxRules){
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0){
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)  startIndex = commentStart.indexIn(text);
    while (startIndex >= 0){
        int endIndex = commentEnd.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1){
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else  commentLength = endIndex - startIndex + commentEnd.matchedLength();
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStart.indexIn(text, startIndex + commentLength);
    }
}
