#include <stdio.h>

#define MAX 100

int price[MAX];
int span[MAX];
int count = 0;

// Calculate stock spans using Stack
void calculateSpan()
{
    int stack[MAX];
    int top = -1;
    int i;

    for (i = 0; i < count; i++)
    {
        while (top != -1 &&
               price[stack[top]] <= price[i])
        {
            top--;
        }

        if (top == -1)
            span[i] = i + 1;
        else
            span[i] = i - stack[top];

        stack[++top] = i;
    }
}

// Add a new stock price
void addPrice()
{
    int p;

    if (count >= MAX)
    {
        printf("\nMaximum history limit reached!\n");
        return;
    }

    printf("\nEnter new stock price: ");
    scanf("%d", &p);

    if (p <= 0)
    {
        printf("Enter a valid positive price!\n");
        return;
    }

    price[count] = p;
    count++;

    calculateSpan();

    printf("\nStock price added successfully!\n");
    printf("Day: %d\n", count);
    printf("Price: %d\n", p);
    printf("Span: %d\n", span[count - 1]);
}

// Display historical records
void displayHistory()
{
    int i;

    if (count == 0)
    {
        printf("\nNo stock records available!\n");
        return;
    }

    printf("\n========== STOCK HISTORY ==========\n");
    printf("Day\tPrice\tSpan\n");

    for (i = 0; i < count; i++)
    {
        printf("%d\t%d\t%d\n",
               i + 1, price[i], span[i]);
    }
}

// Display stock price graph
void displayGraph()
{
    int i, j;
    int maxPrice = 0;
    int barLength;

    if (count == 0)
    {
        printf("\nNo data available!\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (price[i] > maxPrice)
            maxPrice = price[i];
    }

    printf("\n======= STOCK PRICE VISUALIZER =======\n");

    for (i = 0; i < count; i++)
    {
        barLength = (price[i] * 40) / maxPrice;

        printf("Day %d | ", i + 1);

        for (j = 0; j < barLength; j++)
            printf("*");

        printf(" %d\n", price[i]);
    }
}

// Display stock span separately
void displaySpans()
{
    int i;

    if (count == 0)
    {
        printf("\nNo data available!\n");
        return;
    }

    printf("\n======= STOCK SPAN RESULTS =======\n");

    for (i = 0; i < count; i++)
    {
        printf("Day %d : Span = %d\n",
               i + 1, span[i]);
    }
}

// Main function
int main()
{
    int choice;
    int n, i;

    printf("====================================\n");
    printf(" REAL-TIME STOCK SPAN VISUALIZER\n");
    printf("====================================\n");

    printf("\nEnter initial number of days: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX)
    {
        printf("Invalid number of days!\n");
        return 0;
    }

    printf("\nEnter stock prices:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &price[i]);

        if (price[i] <= 0)
        {
            printf("Invalid stock price!\n");
            return 0;
        }

        count++;
    }

    calculateSpan();

    do
    {
        printf("\n\n========== MAIN MENU ==========");
        printf("\n1. Add New Stock Price");
        printf("\n2. Display Stock History");
        printf("\n3. Calculate Stock Spans");
        printf("\n4. Display Stock Graph");
        printf("\n5. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPrice();
                break;

            case 2:
                displayHistory();
                break;

            case 3:
                displaySpans();
                break;

            case 4:
                displayGraph();
                break;

            case 5:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}