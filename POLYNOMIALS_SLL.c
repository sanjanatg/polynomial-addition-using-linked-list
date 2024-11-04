#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int expo;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Polynomial;

void insertTerm(Polynomial* poly, int coeff, int expo) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Insufficient memory\n");
        exit(0);
    }
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;

    if (poly->head == NULL) {
        poly->head = newNode;
    } else {
        Node* temp = poly->head;
        Node* prev = NULL;
        while (temp != NULL && temp->expo > expo) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL && temp->expo == expo) {
            temp->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp;
            if (prev == NULL) {
                poly->head = newNode;
            } else {
                prev->next = newNode;
            }
        }
    }
}

Polynomial addPolynomials(Polynomial* p1, Polynomial* p2) {
    Polynomial result;
    result.head = NULL;

    Node* term1 = p1->head;
    Node* term2 = p2->head;

    while (term1 != NULL) {
        insertTerm(&result, term1->coeff, term1->expo);
        term1 = term1->next;
    }

    while (term2 != NULL) {
        insertTerm(&result, term2->coeff, term2->expo);
        term2 = term2->next;
    }

    return result;
}

void displayPolynomial(Polynomial* poly) {
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
    Polynomial p1, p2;
    p1.head = NULL;
    p2.head = NULL;

    int numPolynomials, numTerms, coeff, expo;
    printf("Enter the number of polynomials: ");
    scanf("%d", &numPolynomials);

    for (int i = 0; i < numPolynomials; i++) {
        printf("\nEnter the number of terms in polynomial %d: ", i + 1);
        scanf("%d", &numTerms);
        for (int j = 0; j < numTerms; j++) {
            printf("Enter the coefficient  of term %d: ", j + 1);

            scanf(" %d", &coeff);
            printf("Enter the exponent for term %d: ", j + 1);
            scanf(" %d", &expo);
            insertTerm((i == 0) ? &p1 : &p2, coeff, expo);
        }
    }

    Polynomial result = addPolynomials(&p1, &p2);
    printf("\n----------- Resulting Polynomial -----------\n");
    displayPolynomial(&result);

    return 0;
}
