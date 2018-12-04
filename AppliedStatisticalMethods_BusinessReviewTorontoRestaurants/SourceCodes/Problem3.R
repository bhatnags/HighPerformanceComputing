#Is there any association between neighborhoods and restaurant categories?Can
#you identify neighbourhoods that are more likely to contain certain types of
#restaurant category than others?
rm(list = ls())
setwd("F://HPC//7DS3//LABS")
getwd()

#Mixture Models
#In this lab we will investigate how to fit models to univariate normal and multivariate noraml and categorical data. To do this we will use the mclust and BayesLCA packages. You will learn:
  
#How to generate mixtures of univariate normal data;
#How to visualise the data to be analysed;
#Fit mixture models to data using EM algorithms and Gibbs sampling;
#Interpret and assess the model output;
#Assess computational issues associated with both methods.


library(BayesLCA)

df_bus_TO <- stream_in(file("business_open_Toronto.json"))
df_bus_TO <- flatten(df_bus_TO)
df_test<- df_bus_TO;
test <- subset(df_test,select = c("neighborhood","categories"))


enocode_neighbour <- as.numeric(as.factor(test$neighborhood))
#enocode_categories <- as.numeric(as.factor(test$categories))
df_bus_TO_encoded = cbind(enocode_neighbour,splitstackshape:::charMat(test$categories, fill = 0))

?charMat #create a binary matrix from a list of character values
?splitstackshape # stack and reshape after splitting concatenated values

#df_bus_TO_encoded = cbind(test,splitstackshape:::charMat(test$categories, fill = 0),splitstackshape:::charMat(test$neighborhood, fill = 0))
df_bus_TO_encoded$categories <- NULL
df_bus_TO_encoded$neighborhood <- NULL 
fit_lca72 <- blca.em(df_bus_TO_encoded, 72,restarts = 30)

fit_lca5 <- blca.em(df_bus_TO_encoded, 5)

plot(fit_lca, which = 1)

table(MAP(Zscore(df_bus_TO_encoded[,-1], fit_lca5)), MAP(Zscore(df_bus_TO_encoded[,-1], fit_lca72)))

ncol(df_bus_TO_encoded)
#_______________________________________________Question 3 Revised___________________________________________________________


df_bus_TO <- stream_in(file("https://www.scss.tcd.ie/~arwhite/Teaching/CS7DS3/business_open_Toronto.json"))
df_bus_TO <- flatten(df_bus_TO)

# neighbourhood- numeric | categories - one hot encoding  
#encoded_neighbourhoods <- as.numeric(as.factor(df_bus_TO$neighborhood))
#df_bus_TO_encoded = cbind(neighborhood=encoded_neighbourhoods,splitstackshape:::charMat(df_bus_TO$categories, fill = 0)) 
##############################

# nuumeric encoding for both
###df_bus_TO_encoded <-cbind(as.numeric(as.factor(df_bus_TO$neighborhood)), as.numeric(as.factor(df_bus_TO$categories))) 
############################## 

bus_cat_tidy <- cbind(df_bus_TO[1, ]$business_id, df_bus_TO[1, ]$categories[[1]])
for(i in 2:nrow(df_bus_TO)) bus_cat_tidy <- rbind(bus_cat_tidy, cbind(df_bus_TO[i, ]$business_id, df_bus_TO[i, ]$categories[[1]]))

cat_names <- names(sort(table(bus_cat_tidy[, 2]), decreasing = TRUE))[2:10] 
cat_bus_ind_mat <- t(sapply(tapply(bus_cat_tidy[, 2], bus_cat_tidy[, 1], function(y) cat_names %in% y), function(x) x*1)) 
nrow(cat_bus_ind_mat)
colnames(cat_bus_ind_mat) <- cat_names


df_cat <- data.frame(ind = rownames(cat_bus_ind_mat), cat_bus_ind_mat)
business_merge <- merge(df_bus_TO, df_cat, by.x = "business_id", by.y = "ind")
# just get neighbourhoods and 9 categories 

# this to get last 9 categories 
df_bus_TO_encoded <- business_merge[,(ncol(business_merge)-8):ncol(business_merge)]

df_bus_TO_encoded$neighborhood <- as.numeric(as.factor(df_bus_TO$neighborhood))

library(mclust)
fit_mclust <- Mclust(df_bus_TO_encoded, G = 3)
plot(fit_mclust, what = "uncertainty")
     

sapply(df_bus_TO_encoded, function(x) sum(is.na(x)))


warnings()
plot(df_bus_TO_encoded$neighborhood,df_bus_TO_encoded[,2:8])
ggplot(df_bus_TO_encoded) + geom_point(aes(neighborhood, df_bus_TO_encoded[,2:8]))
#fit_lca1 <- blca.em(df_bus_TO_encoded, 5)
#fit_lca2 <- blca.em(df_bus_TO_encoded, 10)
#plot(fit_lca,which=1)
#summary(fit_lca)

bic_values <- list()

for(i in 1:length(cat_names)) {
  fit <- blca.em(df_bus_TO_encoded, i)
  bic_values[[i]] <-fit$BIC
}

fit3 <- blca.em(df_bus_TO_encoded, 3) 
fit8 <- blca.em(df_bus_TO_encoded, 8) 
fit6 <- blca.em(df_bus_TO_encoded, 6)
fit9 <- blca.em(df_bus_TO_encoded, 9)
fit4 <- blca.em(df_bus_TO_encoded, 4)
?blca.em


fit <- list()
bic_values <- list()

for(i in 1:10) {
  fit[[i]] <- blca.em(df_bus_TO_encoded, i)
#  bic_values[[i]] <-fit$BIC
#  sd[[i]] <- blca.em(df_bus_TO_encoded, i, sd = TRUE)
}



par(mfrow=c(3,3))
for(i in 2:10) {
plot(fit[[i]], which = 1)
}

par(mfrow=c(3,3))
for(i in 2:10) {
plot(fit[[i]], which = 5)
}

par(mfrow=c(1,1))
plot(fit[[10]], which = 1)

?plot

fit_gibbs <- blca.gibbs(df_bus_TO_encoded, 2, thin = 0.25, iter = 20000)
print(fit_gibbs)
plot(as.mcmc(fit_gibbs)) 


#fit10 <- blca.em(df_bus_TO_encoded, 10)
plot(bic_values)
fit10$BIC
lapply(bic_values, function(x) x[which.max(abs(x))])

?Zscore
table(MAP(Zscore(!is.na(df_bus_TO_encoded[,-1]),fit9)), 
      MAP(Zscore(!is.na(df_bus_TO_encoded[,-1]),fit4)))
plot(fit3, which = 1)
plot(fit3, which = 5)
plot(fit9, which = 1)
plot(fit9, which = 5)




?Zscore

neighborhood <-as.factor(df_bus_TO$neighborhood) 
table(MAP(Zscore(!is.na(df_bus_TO_encoded[,-1]),fit[[10]]))) # Find the class probalitlites for each data points
table(MAP(Zscore(df_bus_TO_encoded[, -1], fit3)),df_bus_TO_encoded$neighborhood) # Assign each data point to a class based on the maximum posterior

a <- plot(table(MAP(Zscore(is.na(df_bus_TO_encoded[, -1]), fit[[5]] )),
              df_bus_TO_encoded$neighborhood), main = "Neighborhood categories") +
  coord_flip() + text(df_bus_TO_encoded[, -1])


    text(table(MAP(Zscore(!is.na(df_bus_TO_encoded[, -1]), fit[[5]]))), 
       y=par()$usr[1]-0.1*(par()$usr[2]-par()$usr[1]),
       labels =levels(df_bus_TO_encoded$neighborhood), 
       srt = 45, adj=1,xpd=TRUE)

axis(1,at=df_bus_TO_encoded$neighborhood,xaxt="n",xlab="") +
axis(2,yaxt="n",ylab="Neighborhooods") 


ggplot(data=as.data.frame(table(MAP(Zscore(!is.na(df_bus_TO_encoded[, -1]), 
                                           fit3)),
                                df_bus_TO_encoded$neighborhood)), 
       aes(weight = Freq, fill=, x=product(Class, Age))) 

install.packages("ggplot")
library(ggplot2)
    geom_mosaic()

library(ggmosaic)
install.packages("ggmosaic")
#attempt by neenu
a <- table(MAP(Zscore(!is.na(df_bus_TO_encoded[, -1]), fit3)),df_bus_TO_encoded$neighborhood)

neighborhood<- unique(df_bus_TO_encoded$neighborhood, incomparables = FALSE)
ggplot(as.data.frame(a),aes(x=neighborhood,y=Freq,fill =Var1 ))+
  geom_bar(stat = "identity", position="stack")+
  theme(axis.text.x=element_text(angle=90, hjust=1))+coord_flip() +
  theme(legend.position = "top")

ggplot(as.data.frame(a),aes(x=neighborhood,y=Freq,fill =Var1 ))+
  geom_bar(stat = "identity", position="dodge")+
  theme(axis.text.x=element_text(angle=90, hjust=1))+
  coord_flip() +
  theme(legend.position = "top")

testy <- df_bus_TO[df_bus_TO$neighborhood == "Downtown Core", ]
