use rand::Rng;

// Converte temperatura de Celsius para Fahrenheit
fn celsius_to_fahrenheit(celsius: f64) -> f64 {
    // Fórmula padrão: (°C × 1.8) + 32
    celsius * 1.8 + 32.0
}

// Imprime os primeiros `n` números da sequência de Fibonacci
fn print_fibonacci(n: usize) {
    let mut a = 0;
    let mut b = 1;
    for _ in 0..n {
        println!("{}", a); // imprime o próximo número
        let temp = a; // guarda o valor de 'a' antes de atualizar
        a = b;        // 'a' recebe o valor de 'b'
        b = temp + b; // 'b' vira a soma de 'a' anterior + 'b' anterior
    }
}

// Encontra o maior valor em um array
fn max_in_array(arr: &[i32]) -> Option<i32> {
    if arr.is_empty() {
        return None; // retorna None se o array estiver vazio
    }

    let mut max = arr[0]; // assume que o primeiro é o maior por enquanto
    for &item in arr.iter() {
        if item > max {
            max = item; // atualiza o maior valor encontrado
        }
    }
    Some(max)
}

// Verifica se um número é primo de forma ingênua (bruta)
fn is_prime_brute(n: u128) -> bool {
    if n <= 1 {
        return false;
    }

    // Verifica divisores de 2 até n^(1/2)
    for i in 2..=((n as f64).sqrt() as u128) {
        if n % i == 0 {
            return false; // achou um divisor, não é primo
        }
    }
    true
}

// Teste de primalidade probabilístico (Miller-Rabin simplificado)
//essa função não funciona com os números de Carmichael (compostos)
fn is_prime_probabilistic(n: u128, k: u32) -> bool {
    if n <= 3 {
        return n > 1; // 2 e 3 são primos
    }
    if n % 2 == 0 {
        return false; // par não é primo
    }

    // Escreve n - 1 como 2^r * d
    let mut d = n - 1;
    let mut r = 0;
    while d % 2 == 0 {
        d = d / 2;
        r = r + 1;
    }

    let mut rng = rand::thread_rng();

    'testes: for _ in 0..k {
        let a = rng.gen_range(2..n - 2); // escolhe um número aleatório
        let mut x = mod_pow(a, d, n); // calcula a^d mod n
        if x == 1 || x == n - 1 {
            continue; // pode ser primo, continua testando
        }

        for _ in 0..r - 1 {
            x = mod_pow(x, 2, n);
            if x == n - 1 {
                continue 'testes;
            }
        }
        return false; // provavelmente composto
    }

    true // provavelmente primo
}

// Função auxiliar para calcular (base^exp) % modulus -> evitar overflow
fn mod_pow(mut base: u128, mut exp: u128, modulus: u128) -> u128 {
    let mut result = 1; // Começamos com o valor neutro da multiplicação

    base = base % modulus; // Garantimos que a base está dentro do módulo

    while exp > 0 {
        // Se o expoente for ímpar, multiplicamos o resultado pela base
        if exp % 2 == 1 {
            result = (result * base) % modulus;
        }

        // Elevamos a base ao quadrado (modularmente)
        base = (base * base) % modulus;

        // Dividimos o expoente por 2
        exp = exp / 2;
    }

    return result;
}


// Verifica se uma string é um palíndromo (ignora espaços)
fn is_palindrome(s: &str) -> bool {
    let chars: Vec<char> = s.chars().collect();
    let mut i = 0;
    let mut j = chars.len() - 1;

    while i < j {
        // pula espaços à esquerda
        while i < j && chars[i] == ' ' {
            i += 1;
        }
        // pula espaços à direita
        while i < j && chars[j] == ' ' {
            j -= 1;
        }

        // compara os caracteres
        if chars[i] != chars[j] {
            return false;
        }

        i += 1;
        j -= 1;
    }

    return true;
}

// Filtra e retorna apenas os primos de um vetor
fn filter_primes(vec: Vec<u32>) -> Vec<u32> {
    let mut resultado = vec![0; vec.len()]; // vetor do mesmo tamanho que o original
    let mut j = 0; // índice de onde vamos colocar o próximo primo

    let mut i = 0;
    while i < vec.len() {
        let n = vec[i];
        if is_prime_brute(n as u128) {
            resultado[j] = n;
            j += 1;
        }
        i += 1;
    }

    // Criamos um vetor com só os primos, cortando os zeros restantes
    let mut primos = vec![0; j];
    let mut k = 0;
    while k < j {
        primos[k] = resultado[k];
        k += 1;
    }

    return primos;
}

fn main() {
    println!("1. Celsius para Fahrenheit: 25°C = {:.2}°F", celsius_to_fahrenheit(25.0));

    println!("\n2. Primeiros 10 números de Fibonacci:");
    print_fibonacci(10);

    println!("\n3. Maior número no array:");
    let arr = [3, 98, -2, 5, 12];
    println!("Maior valor: {:?}", max_in_array(&arr));

    println!("\n4. Verificação de primos (bruta e probabilística):");
    //carmichaels = [561, 1105, 1729, 2465, 2821, 6601, 8911]
    let numero = 6601u128;
    println!("{} é primo (bruta)? {}", numero, is_prime_brute(numero));
    //is_prime_probabilistic(primo, k) -> k é o número de vezes que o teste vai ser refeito
    println!("{} é primo (probabilístico)? {}", numero, is_prime_probabilistic(numero, 5));

    println!("\n5. Verificação de palíndromo:");
    let palavra = "oi rato otario";
    println!("'{}' é palíndromo? {}", palavra, is_palindrome(palavra));

    println!("\n6. Filtro de primos em vetor:");
    let numeros = vec![10, 11, 12, 13, 14, 15, 16, 17, 18, 19];
    let primos = filter_primes(numeros);
    println!("Primos encontrados: {:?}", primos);
}

