# This assignment will consist of a report, with a maximum length of 20 pages.
# Analyse the Yelp academic dataset: https://www.yelp.com/dataset.
# Analysis on restaurant businesses that are currently open in the city of Toronto.
# The assignment is worth 70% of the module mark, and will be evaluated
# Data management (10%)
# Clarity of writing and exposition (10%)
# Modelling (60%)
# Creativity (20%)

remove(list = ls())
setwd("F://HPC//7DS3//LABS")
getwd()
# Compare the ratings of dierent neighbourhoods.
# Are any neighbourhoods clearly superior to others? If so, by how much?

library("jsonlite")
library("ggplot2")
library("readr")

senti <- stream_in(file("review_sentiment_Toronto_full.json"))
nrow(review) #216006
length(unique(review$business_id))#4028
names(review)
length(unique(review$review_id))#216006

df_bus_rev <- read.csv2("review_bus_S.csv",sep = ",")
nrow(df_bus_rev) #216006
length(unique(df_bus_rev$business_id))#3977
length(unique(df_bus_rev$neighborhood))#3977
names(df_bus_rev)
length(unique(df_bus_rev$review_id))#213372
length(unique(df_bus_rev$user_id))#213372


lm(review$stars ~ ., review)


unique(df_bus_rev$attributes.RestaurantsPriceRange2, incomparables = FALSE)
df_bus_rev_subset <- stream_in(file("review_bus_S.json"))


df_bus_rev <- read.csv2("/Users/sethuram/Desktop/ASM_ASSIGNMENT/review_bus_merged.csv",sep = ",")
*
df_bus_rev <- read.csv2("review_bus_S.csv",sep = ",")
names(review)

select_features <- c("funny", "useful",
                     "neighborhood","review_count" ,"stars") #"magnitude","score",

df_bus_rev_subset <- subset(df_bus_rev, select=select_features)
str(df_bus_rev_subset)

#--------------------------Dataset transformation------------------------#
df_bus_rev_subset$magnitude <- as.numeric(df_bus_rev_subset$magnitude )
df_bus_rev_subset$score <- as.numeric(df_bus_rev_subset$score )
df_bus_rev_subset$stars<- as.numeric(as.character(df_bus_rev_subset$stars ))
#df_bus_rev_subset$neighborhood <- factor(as.numeric((df_bus_rev_subset$neighborhood)))
#df_bus_rev_subset$attributes.RestaurantsPriceRange2 <- as.character(df_bus_rev_subset$attributes.RestaurantsPriceRange2)
#df_bus_rev_subset$attributes.RestaurantsPriceRange2[df_bus_rev_subset$attributes.RestaurantsPriceRange2 == ""]<- "0.0"
#df_bus_rev_subset$attributes.RestaurantsPriceRange2<-factor(df_bus_rev_subset$attributes.RestaurantsPriceRange2)

#--------------------------Feature Selection------------------------#
#extra..

correlation_features <- c("cool","funny","review_stars", "useful","review_count" ,"stars")
#correlation_features <- c("funny","magnitude","score","review_stars", "useful","review_count" ,"stars")

df_bus_rev$magnitude <- as.numeric(df_bus_rev$magnitude )
df_bus_rev$score <- as.numeric(df_bus_rev$score )
df_bus_rev$stars <-   as.numeric(as.character(df_bus_rev_subset$stars ))
df_bus_rev_correlation_subset <- subset(df_bus_rev, select=correlation_features)
str(df_bus_rev_correlation_subset)
cor(df_bus_rev_correlation_subset)

cex.before <- par("cex")
# par can be used to set or query graphical parameters. 
# Parameters can be set by specifying them as arguments to par in tag = value form, 
# or by passing them as a list of tagged values.

# A numerical value giving the amount by which 
# plotting text and symbols should be magnified relative to the default.

install.packages("corrplot")
library(corrplot)
corrplot(cor(df_bus_rev_correlation_subset),method = "number",
         tl.col = "black",type = "lower",tl.cex = 1.5,
         cl.cex = 1,tl.srt=45)
#--------------------------Feature Selection-------using AIC -----------------#
model_features <- c("cool","funny","review_stars", "useful","attributes.RestaurantsPriceRange2","neighborhood","review_count" ,"stars")
df_bus_rev_subset_model_selection <- subset(df_bus_rev, select=model_features)

lm1 <- lm(stars~., df_bus_rev_subset_model_selection)
summary(lm1)

##Feature Selection #########
step_AIC <- step(lm1)
step_BIC <- step(lm1, k=log(nrow(df_bus_rev_subset_model_selection))) 

print(step_AIC)

#-------------------------Model Building-----------------#

fit<- MCMCregress(stars~., data=df_bus_rev_subset)
summary(fit)
plot(fit)
beta_mean <- apply(fit, 2, mean)
beta_mean <- as.data.frame(beta_mean)
beta_mean["variables"]<- attributes(beta_mean)$row.names

new <- c(4.728706e+00,"attributes.RestaurantsPriceRange20.0")
beta_mean <- InsertRow(beta_mean, new, 
                       RowNum = which(beta_mean$variables=="attributes.RestaurantsPriceRange21.0"))
?InsertRow
table(beta_mean)

which(beta_mean$variables=="attributes.RestaurantsPriceRange22") 

new2 <- c(4.728706e+00,"neighborhood1")
beta_mean <- InsertRow(beta_mean, new2, RowNum = which(beta_mean$variables=="neighborhood2"))
beta_mean <- beta_mean[-nrow(beta_mean),]

select_feature_subset <- c("funny","review_stars", "useful")
df_dummy<-  subset(df_bus_rev_subset, select=select_feature_subset)
df_dummy2 <- as.data.frame(cbind(splitstackshape:::charMat( df_bus_rev_subset$attributes.RestaurantsPriceRange2, fill = 0),splitstackshape:::charMat( factor(as.numeric((df_bus_rev_subset$neighborhood))), fill = 0)))
df_dummy <- cbind.data.frame(1,df_dummy,df_dummy2,df_bus_rev_subset$review_count)
dim(df_dummy) 
dim(as.matrix(beta_mean) ) 
str(dim(df_dummy)) 
str(as.matrix(beta_mean))
beta_mean$variables<-NULL
beta_mean$beta_mean <- as.numeric(beta_mean$beta_mean)
pred_fit <- as.matrix(df_dummy) %*% as.matrix(beta_mean) 
plot(pred_fit, df_bus_rev_subset$stars)
pred_fit[is.na(pred_fit)] <-0
hist(pred_fit)
a<-
  str(a)
ggplot(data=as.data.frame(pred_fit), aes(beta_mean)) + geom_histogram(binwidth = 0.5,breaks=seq(1, 10, by =0.5),col="red", 
                                                                      aes(fill=..count..)) +
  scale_fill_gradient("Count", low = "blue", high = "red")
RMSE(pred_fit,df_bus_rev_subset$stars)


#-------------------------adding quadratic---------------------------------------#

select_features <- c("funny","magnitude","score","review_stars", "useful","attributes.RestaurantsPriceRange2","neighborhood","review_count" ,"stars")

formula_quadratic <-  stars ~funny+magnitude+score+review_stars+useful+attributes.RestaurantsPriceRange2+neighborhood+review_count+ I(magnitude^2) + I(score^2)
fit_stars <- MCMCregress(formula_quadratic, data=df_bus_rev_subset) #subset of 1000
beta_mean <- apply(fit_stars, 2, mean)
beta_mean <- as.data.frame(beta_mean)
beta_mean["variables"]<- attributes(beta_mean)$row.names
Intercept <-as.numeric(beta_mean[1,]$beta_mean)
beta_mean <- beta_mean[-nrow(beta_mean),]


new <- c(1,"attributes.RestaurantsPriceRange20.0")
beta_mean <- InsertRow(beta_mean, new, RowNum = which(beta_mean$variables=="attributes.RestaurantsPriceRange21.0"))
new2 <- c(Intercept,"neighborhood1")
beta_mean <- InsertRow(beta_mean, new2, RowNum = which(beta_mean$variables=="neighborhood2"))
beta_mean$beta_mean <- as.numeric(beta_mean$beta_mean)
rownames(beta_mean) <- c()
rownames(beta_mean) <- beta_mean[,2]
beta_mean["variables"]<-NULL

select_feature_subset <- c("funny","magnitude","score","review_stars", "useful")
df_dummy<-  subset(df_bus_rev_subset, select=select_feature_subset)
df_dummy2 <- as.data.frame(cbind(splitstackshape:::charMat( df_bus_rev_subset$attributes.RestaurantsPriceRange2, fill = 0),splitstackshape:::charMat( factor(as.numeric((df_bus_rev_subset$neighborhood))), fill = 0)))
df_dummy <- cbind.data.frame(1,df_dummy,df_dummy2,df_bus_rev_subset$review_count,df_bus_rev_subset[, c(2, 3)]^2)

dim(df_dummy) dim(as.matrix(as.numeric(beta_mean))) str(beta_mean) str(df_dummy)
pred_fit <- as.matrix(df_dummy) %*% as.matrix(beta_mean) # make prediction, ignore variance parameter

plot(pred_fit, df_bus_rev_subset$stars)
RMSE(pred_fit,df_bus_rev_subset$stars)
hist(pred_fit)
ggplot(data=as.data.frame(pred_fit), aes(beta_mean)) + geom_histogram(binwidth = 0.5,breaks=seq(1, 10, by =0.5),col="red", 
                                                                      aes(fill=..count..)) +
  scale_fill_gradient("Count", low = "red", high = "blue")





'
business <- stream_in(file("business.json"))
review <- stream_in(file("review.json"))
user <- stream_in(file("user.json"))
business <- flatten(business)
review <- flatten(review)
user <- flatten(user)
head(business)
dim(business)
head(review)
dim(review)
head(user)
dim(user)

neigh <- neigh[business$neighborhood!='',]
#106552+68015
neigh <- neigh[neigh$neighborhood=='',]
new_DF_open <- df_bus_TO[df_bus_TO$is_open==1,]
new_DF_closed <- new_DF[new_DF$is_open==0,]
#55518+12497

new_DF_open$neighborhood <- factor(new_DF_open$neighborhood)
nlevels(new_DF_open$neighborhood)

sapply(new_DF_open, class)
typeof(new_DF_open$categories)
new_DF_open$categories <- as.character(new_DF_open$categories)

write.csv(new_DF_open, file="F://hpc//7DS3//new_DF.csv")

business$neighborhood <- factor(business$neighborhood)

nlevels(business$neighborhood)

ggplot(business) + 
  geom_boxplot(aes(x = reorder(business$neighborhood, business$stars, median), 
                   business$stars, fill = reorder(business$neighborhood, business$stars, median)), 
               show.legend=FALSE)


ggplot(business, aes(x = reorder(neighborhood, neighborhood, length))) + stat_count()

tapply(df_bus_TO$stars, df_bus_TO$neighborhood, mean)

as.data.frame(table(df_bus_TO$neighborhood)) -> neighborhood_freq

ggplot(new_DF) + 
  geom_boxplot(aes(x = reorder(new_DF$neighborhood, new_DF$stars, median), 
                   new_DF$stars, fill = reorder(new_DF$neighborhood, new_DF$stars, median)), 
               show.legend=FALSE)

ggplot(new_DF, aes(x = reorder(neighborhood, neighborhood, length))) + stat_count()


ggplot(df_bus_TO, aes(stars)) + stat_bin()


ggplot(data.frame(size = tapply(df_bus_TO$stars, df_bus_TO$neighborhood, length), 
                  mean_rating = tapply(df_bus_TO$stars, df_bus_TO$neighborhood, mean)), 
       aes(size, mean_rating)) + geom_point()

'
