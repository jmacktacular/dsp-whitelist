# DSP Whitelist

A whitelisting contract for DSPs to control who registers with them



## Quickstart

```
./build.sh
./deploy.sh
./test.sh
```


## ACTIONS

- [`add`](#action-add)
- [`remove`](#action-remove)
- [`checklist`](#action-checklist)

## TABLES

- [`whitelist`](#table-whitelist)


### ACTION `add`

Adds user to whitelist table

### params
    
- `@param {name} account` - EOSIO account name to whitelist
- `@param {name} service` - DSP service
- `@param {name} package` - DSP package name

### example

```js
Add ("myaccount","ipfsservic1","package1")
```

 
### ACTION `remove`

Removes user from whitelist table

### params
    
- `@param {name} account` - EOSIO account name to whitelist
- `@param {name} service` - DSP service
- `@param {name} package` - DSP package name

### example
  
```js
remove ("myaccount","ipfsservic1","package1")
```


### ACTION `checklist`     

Checks if account name is authorized to use this package

### params
    
- `@param {name} account` - EOSIO account name to whitelist
- `@param {name} service` - DSP service
- `@param {name} package` - DSP package name

### example
    
```js
checklist ("myaccount","ipfsservic1","package1")
```



### TABLE `whitelist`

Contains all information related to the whitelist
    
### params

- `@param {unit64_t} id`  - Identifier for whitelist entry
- `@param {name} account` - EOSIO account name to whitelist
- `@param {name} service` - DSP service
- `@param {name} package` - DSP package name

### example

```json
     {
       "id": 0,
       "account": "myaccount",
       "service": "ipfsservice1",
       "package": "package1"
     }
``` 
