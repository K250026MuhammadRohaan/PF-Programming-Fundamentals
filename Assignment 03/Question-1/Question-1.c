#include <stdio.h>

double calculateRepayment(double loan, double interestRate, double installment, int year, int totalYears)
{
    if (loan <= 0 || year > totalYears) {
        return 0;
    }

    loan += loan * (interestRate / 100.0);

    loan -= installment;
    if (loan < 0) loan = 0;

    printf("Year %d: Remaining loan = %.2f\n", year, loan);

    return installment + alculateRepayment(loan, interestRate, installment, year + 1, totalYears);
}

int main() {
    double loan, rate, installment;
    int years;

    printf("Enter initial loan amount: ");
    scanf("%lf", &loan);

    printf("Enter yearly interest rate (%%): ");
    scanf("%lf", &rate);

    printf("Enter number of years: ");
    scanf("%d", &years);

    printf("Enter yearly installment: ");
    scanf("%lf", &installment);

    printf("\n--- Repayment Schedule ---\n");
    double totalPaid = calculateRepayment(loan, rate, installment, 1, years);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalPaid);

    return 0;
}