# GNU Makefile
JAR=/usr/local/jdk1.8.0_131/bin/jar
JAVA=/usr/local/jdk1.8.0_131/bin/java
JAVAC=/usr/local/jdk1.8.0_131/bin/javac

CP=.:/usr/local/rabbitmq-jar/amqp-client-4.0.2.jar:/usr/local/rabbitmq-jar/slf4j-api-1.7.21.jar:/usr/local/rabbitmq-jar/slf4j-simple-1.7.22.jar
JFLAGS = -g -cp $(CP)

SRC_DIR_KOMPRAO=komprao/src
SRC_DIR_FORNECEDOR=fornecedor
SRC_DIR_TRANSPORTADORA=transportadora
UTILS=utils

BIN_DIR=bin

# Encontrar todos os .java recursivamente
SOURCES_KOMPRAO=$(shell find $(SRC_DIR_KOMPRAO) -name "*.java")
SOURCES_FORNECEDOR=$(shell find $(SRC_DIR_FORNECEDOR) -name "*.java")
SOURCES_TRANSPORTADORA=$(shell find $(SRC_DIR_TRANSPORTADORA) -name "*.java")
SOURCE_UTILS=$(shell find $(UTILS) -name "*.java")

# Alvo padrão
all: compile

ServerEstoque: 
	$(JAVA) -cp $(BIN_DIR) server.ServerEstoque 

ServerServidor:
	$(JAVA) -cp $(BIN_DIR) server.ServerServidor

Caixa:
	$(JAVA) -cp $(BIN_DIR) caixa.Caixa

Fornecedor:
	$(JAVA) -cp $(CP):$(BIN_DIR) fornecedor.FornecedorServerPublisher

Transportadora: 
	$(JAVA) -cp $(CP):$(BIN_DIR) transportadora.Recv

run:
	$(JAVA) -cp $(CP):$(BIN_DIR) transportadora.Recv; exec bash 
	sleep 2
	$(JAVA) -cp $(CP):$(BIN_DIR) caixa.FornecedorServerPublisher 
	sleep 2
	$(JAVA) -cp $(BIN_DIR) server.ServerEstoque 
	sleep 2
	$(JAVA) -cp $(BIN_DIR) caixa.Caixa




# Compilar os .java para .class dentro de bin/
compile:
	mkdir -p $(BIN_DIR)
	$(JAVAC) -d $(BIN_DIR) $(SOURCE_UTILS)
	$(JAVAC) -d $(BIN_DIR) $(SOURCES_KOMPRAO)
	$(JAVAC) -cp $(CP) -d $(BIN_DIR) $(SOURCES_FORNECEDOR)
	$(JAVAC) -cp $(CP) -d $(BIN_DIR) $(SOURCES_TRANSPORTADORA)
	@echo 'Compilation Completed'

# Limpar os .class
clean:
	rm -rf $(BIN_DIR)
