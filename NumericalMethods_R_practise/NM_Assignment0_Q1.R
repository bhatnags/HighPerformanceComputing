#Define length of matrix
p=4; q=4;

#Create Matrix
matrix_input<-matrix(1:16, nrow=p,ncol=q, byrow = FALSE)
matrix_input

#Create matrix function "turned" to rotate the matrix anticlockwise
turned_output <- function(turned) apply(matrix_input, 1,rev)
turned_output(turned)


