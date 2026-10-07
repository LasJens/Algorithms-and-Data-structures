function Check(operation, maxAttempts, initialDelayMs) {
    let attempt = 1;
    
    function Attempt() {  
        return operation()
            .then(result => {
                console.log(`Success`);
                return result;
            })
            .catch(error => {
                console.log(`Fail ${attempt}:`, error.message);
                
                if (attempt >= maxAttempts) {
                    console.log(`Grand fail`);
                    throw error;
                }

                var Delay = initialDelayMs * Math.pow(2, attempt - 1);
                console.log(`Wait for ${Delay}ms`);
                attempt++;

                return new Promise(resolve => {
                    setTimeout(() => {
                        resolve(Attempt());
                    }, Delay);
                });
            });
    }
    return Attempt();
}

// Тестовая функция, которая иногда падает
function createUnstableOperation(failTimes = 2) {
    let callCount = 0;
    
    return function() {
        callCount++;
        console.log(`Вызов операции №${callCount}`);
        
        return new Promise((resolve, reject) => {
            if (callCount <= failTimes) {
                reject(new Error(`Искусственная ошибка №${callCount}`));
            } else {
                resolve(`Успех после ${callCount} попыток!`);
            }
        });
    };
}

// Тест 1: Функция упадет 2 раза, затем успех
const unstableOp = createUnstableOperation(2);
Check(unstableOp, 5, 100)
    .then(result => {
        console.log('✅ Тест 1 пройден:', result);
    })
    .catch(error => {
        console.log('❌ Тест 1 не пройден:', error.message);
    });