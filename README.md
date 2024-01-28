# @ - Script V1

## create a fuction that returs an int and it is called main

## the main function is the startpoint of every programm

````
@fn main#int {

    //return 0 (0 is sucsecc 1 is an error (only work in the main function)) 
    @back 0

}
````

## basic function statement : 

````
@fn {function-name}#{return-type} : {{type} {value-name}}, {{type} {value-name}} {

    //exmale params : int i,string s,char c,float f 

    @back {return-value}

}
````

## return statement

```
@back {value to return}
```

## import cpp form local file :

```
@add {file-path} 
```

## import from cpp libary:

```
@imp {name} 
```

## create global value :

```
@static {value-name} {value} 
```

## create array (cpp-vector)

```
@array {array-name} : {type}
```

## loop for each item in array (or cpp-vector)

```
@for_each {item-name} in {array-name}
```

## loop

```
@loop {number or value of times the loop will get called} {name for the loop index value}
```