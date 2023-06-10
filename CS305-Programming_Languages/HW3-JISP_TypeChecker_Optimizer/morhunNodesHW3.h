#ifndef __ORHUNNODESHW3_H
#define __ORHUNNODESHW3_H

extern int globalLineNum;

typedef enum { INT_TYPE, REAL_TYPE, STRING_TYPE , NO_TYPE, COMPLETED_TYPE} NodeType;

typedef struct TreeNode {
	NodeType type;
    int validType;
	int printFlag;
    
	int integerValue;
	char * stringValue;
	float realValue;

    int lineNum;

} TreeNode;


#endif