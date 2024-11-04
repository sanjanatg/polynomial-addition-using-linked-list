#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, n, type)               \
    p = (type*)malloc(n*sizeof(type));   \
    if (p == NULL)                       \
    {                                    \
        printf("insufficient memory\n"); \
        exit(0);                         \
    }

typedef struct Node {
    int coeff;
    int expo;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Polynomial;

void insertTerm(Polynomial* poly, int coeff, int expo)
 {
    Node* newNode;
    MALLOC(newNode,1,Node);
    if (!newNode) {
        printf("Insufficient memory\n");
        exit(0);
    }
    //READY THE NODE
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;

    if (poly->head == NULL) 
    { //// INSERTING as 1ST ELEMENT IF LIST WAS EMPTY
        poly->head = newNode;
    } 
    else 
    {   //READY THE TEMP TO TRAVERSE
        Node* cur = poly->head;
        Node* prev = NULL;

        while (cur != NULL && cur->expo > expo) 
        {     //Ensures we haven't reached the end of the list AND , Keeps moving forward as long as the current term's exponent is greater than the new term's exponent.
            prev = cur;
            cur = cur->next;
            /*
            We do this to maintain the linked list in descending order by exponents.
             =This way, when you display the polynomial, it's already sorted and looks like a proper polynomial expression.
             =It’s easier to add like terms together, as similar exponents will be adjacent.
            It makes the polynomial more readable and consistent with standard polynomial notation, */
        }
        
        /*
        When adding a new term, if an existing term has the same exponent, we add their coefficients together to avoid duplicate terms  i.e 
        having multiple nodes for the same exponent value.
        It keeps the polynomial clean and avoids redundancy.
        */
       //---------------disadvantage = cannot access the terms of polynomials entered individually

        if (cur != NULL && cur->expo == expo) 
        {
            cur->coeff += coeff;
            free(newNode);
        }

        // it gets inserted at the appropriate place in the middle or at the end of the list.
        // not inserted at the beginning (the head) of the list
        else
        {
            newNode->next = cur;//This links the new node to the remaining part of the list.
            if (prev == NULL)
            {   //when there’s no previous node, i.e., it’s being inserted at the beginning I.E AS THE HEAD
                poly->head = newNode;
            } 
            else 
            { //it links the previous node to the new node.
                prev->next = newNode;
            }
        }
    }
}

Polynomial addPolynomials(Polynomial* polys, int n) 
{
    //Initialize Result Polynomial
    Polynomial result;
    result.head = NULL;
//Loop Through Polynomial polys:
    for (int i = 0; i < n; ++i) 
    {      //For each polynomial in the input array:
        Node* term = polys[i].head;

        //The insertTerm function takes care of correctly placing each term in the result polynomial, ensuring terms with the same exponent are combined
        while (term != NULL) {
            insertTerm(&result, term->coeff, term->expo);
            term = term->next;
        }
    }
    return result;
}

void displayPolynomial(Polynomial* poly)
{
    Node* temp = poly->head;
    while (temp != NULL) {
        if (temp->coeff != 0) {
            if (temp != poly->head && temp->coeff > 0) {
                printf(" + ");
            }
            printf("%dx^%d ", temp->coeff, temp->expo);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int num;
    printf("Enter the number of polynomials: ");
    scanf("%d", &num);

    Polynomial polys[num];//ARRAY OF STRUCTURE

    for (int i = 0; i < num; ++i) 
    {
        polys[i].head = NULL;
        int numTerms, coeff, expo;

        printf("\nEnter the number of terms in polynomial %d: ", i + 1);
        scanf("%d", &numTerms);

        for (int j = 0; j < numTerms; ++j) 
        {
            printf("Enter the coefficient of term %d: ", j + 1);
            scanf("%d", &coeff);
            printf("Enter the exponent for term %d: ", j + 1);
            scanf("%d", &expo);

            insertTerm(&polys[i], coeff, expo);
        }
    }

    Polynomial result = addPolynomials(polys, num);

    printf("\n----------- Resulting Polynomial -----------\n");
    displayPolynomial(&result);

    return 0;
}
