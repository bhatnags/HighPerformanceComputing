# What variables are most influential at predicting restaurant rating?
# How accurate are these predictions?
remove(list = ls())
setwd("F://HPC//7DS3//LABS")
getwd()


# factors from business file
# address, business_id, categories, city, hours_open, hours_closing, is_open, latitude, longitude, business_name, neighbourhood, postal_Code, review_Count, stars, state
# factors from review file
# business_id, rview, votes, date, review_id, stars, text, user_id, useful, funny, cool
# factors from user file
# user_id, average_Stars, compliment, votes, elite, fans, friends, name, review_Count, type, yelping_sense

x<- read.csv("review_bus_S.csv")

names(x)
names(x)[names(x) == 'stars.x'] <- 'reviewStars'
names(x)[names(x) == 'stars.y'] <- 'restaurantStars'

select_features <- c("restaurantStars", "cool", "useful", "funny", "score", "magnitude","neighborhood")
correlation_subset <- subset(x, select=select_features)
correlation_subset$neighborhood <- (as.numeric((correlation_subset$neighborhood)))
correlation_subset$magnitude <- as.numeric(correlation_subset$magnitude )
correlation_subset$score <- as.numeric(correlation_subset$score )
str(correlation_subset)
cor(correlation_subset)-> corTable
correlation_subset$date <- as.POSIXct(correlation_subset$date, format="%Y-%m-%d %H:%M:%S", tz="GMT")

library(psych)
pairs.panels(correlation_subset)
colnames(x)
sapplyClass <- as.data.frame(sapply(x, class))
par(mar = rep(2, 4))
pairs(x)

cex.before <- par("cex")

corrplot(cor(df_bus_rev_correlation_subset),method = "number",
         tl.col = "black",type = "lower",tl.cex = 1.5,
         cl.cex = 1,tl.srt=45)


df_bus_rev_subset$attributes.RestaurantsPriceRange2 <- as.character(df_bus_rev_subset$attributes.RestaurantsPriceRange2)
df_bus_rev_subset$attributes.RestaurantsPriceRange2[df_bus_rev_subset$attributes.RestaurantsPriceRange2 == ""]<- "0.0"
df_bus_rev_subset$attributes.RestaurantsPriceRange2<-factor(df_bus_rev_subset$attributes.RestaurantsPriceRange2)
df_bus_rev_correlation_subset$stars<- as.numeric(as.character(df_bus_rev_correlation_subset$stars ))

names(df_bus_rev)
select_features <- c("funny","magnitude","score","review_stars", "useful","attributes.RestaurantsPriceRange2","neighborhood","review_count" ,"stars")

df_bus_rev_subset <- subset(df_bus_rev, select=select_features)
str(df_bus_rev_subset)

#--------------------------Dataset transformation------------------------#

#--------------------------Feature Selection------------------------#
#extra..

correlation_features <- c("cool","funny","magnitude","score","review_stars", "useful","review_count" ,"stars")
#correlation_features <- c("funny","magnitude","score","review_stars", "useful","review_count" ,"stars")

df_bus_rev$magnitude <- as.numeric(df_bus_rev$magnitude )
df_bus_rev$score <- as.numeric(df_bus_rev$score )
df_bus_rev$stars <-   as.numeric(as.character(df_bus_rev_subset$stars ))
df_bus_rev_correlation_subset <- subset(x, select=correlation_features)
str(df_bus_rev_correlation_subset)
cor(df_bus_rev_correlation_subset)

cex.before <- par("cex")

corrplot(cor(df_bus_rev_correlation_subset),method = "number",
         tl.col = "black",type = "lower",tl.cex = 1.5,
         cl.cex = 1,tl.srt=45)
#--------------------------Feature Selection-------using AIC -----------------#
model_features <- c("cool","funny","magnitude","score","review_stars", "useful","attributes.RestaurantsPriceRange2","neighborhood","review_count" ,"stars")
df_bus_rev_subset_model_selection <- subset(df_bus_rev, select=model_features)

lm1 <- lm(correlation_subset$restaurantStars~., correlation_subset)
summary(lm1)
anova(lm1)
##Feature Selection #########

step_AIC <- step(lm1)
step_BIC <- step(lm1, k=log(nrow(df_bus_rev_subset_model_selection))) 

print(step_AIC)


#-------------------------Model Building-----------------#
lm1 <- lm(correlation_subset$restaurantStars~., correlation_subset)

library(MCMCpack)
fit<- MCMCregress(restaurantStars ~., data=correlation_subset)
summary(fit)
plot(fit)
beta_mean <- apply(fit, 2, mean)
beta_mean <- as.data.frame(beta_mean)
beta_mean["variables"]<- attributes(beta_mean)$row.names

new <- c(4.728706e+00,"attributes.RestaurantsPriceRange20.0")
beta_mean <- InsertRow(beta_mean, new, RowNum = which(beta_mean$variables=="attributes.RestaurantsPriceRange21.0"))
new2 <- c(4.728706e+00,"neighborhood1")
beta_mean <- InsertRow(beta_mean, new2, RowNum = which(beta_mean$variables=="neighborhood2"))
beta_mean <- beta_mean[-nrow(beta_mean),]

select_feature_subset <- c("funny","magnitude","score","review_stars", "useful")
df_dummy<-  subset(df_bus_rev_subset, select=select_feature_subset)
df_dummy2 <- as.data.frame(cbind(splitstackshape:::charMat( df_bus_rev_subset$attributes.RestaurantsPriceRange2, fill = 0),splitstackshape:::charMat( factor(as.numeric((df_bus_rev_subset$neighborhood))), fill = 0)))
df_dummy <- cbind.data.frame(1,df_dummy,df_dummy2,df_bus_rev_subset$review_count)
dim(df_dummy) dim(as.matrix(beta_mean) ) str(dim(df_dummy)) str(as.matrix(beta_mean))
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