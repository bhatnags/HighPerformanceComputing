#creating the framework of arbitrary input file
table<- matrix(c(1.2, 3.4, 5.6, 7.8,2.3, 4.5, 6.7, 8.9,3.4, 5.6, 7.8, 9.8), ncol = 3, byrow = TRUE)
df<- as.table(table)
df

#creating the arbitrary input file
write.table(df, file = "E://mytable.txt", row.names = FALSE, col.names = FALSE)

#reading the table
new_table<- read.table("E://mytable.txt", sep = " ")
new_table

#printing the mean & standard variation of each column
myresults.txt<- sapply(new_table,function(x) list(mean = mean(x), Std_dev=sd(x)))
myresults.txt

#creating the plot of first column vs second column taking third column as the errorbar values
library(ggplot2)
ggplot(new_table,aes(x=new_table$V1, y=new_table$V2)) +
  geom_line()+
  geom_errorbar(width = 0.1, 
  aes(ymin = new_table$V3, ymax = (new_table$V2*2-new_table$V3)))

                      