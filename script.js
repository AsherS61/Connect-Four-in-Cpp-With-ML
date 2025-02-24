let currentPlayer = 'X';
let gameBoard = Array(6).fill().map(() => Array(7).fill(''));
let gameOver = false;

const titleScreen = document.getElementById('titleScreen');
const gameScreen = document.getElementById('gameScreen');
const board = document.getElementById('board');
const currentPlayerDisplay = document.getElementById('currentPlayer');
const status = document.getElementById('status');
const retryButton = document.getElementById('retryButton');
const goToTitleButton = document.getElementById('goToTitleButton');
const singleplayerButton = document.getElementById('singleplayerButton');
const multiplayerButton = document.getElementById('multiplayerButton');

singleplayerButton.addEventListener('click', startSinglePlayerGame);
multiplayerButton.addEventListener('click', startMultiplayerGame);
retryButton.addEventListener('click', restartGame);
goToTitleButton.addEventListener('click', goToTitleScreen);

// Initializes the game board in the DOM
function createBoard() {
    board.innerHTML = '';
    for (let row = 0; row < 6; row++) {
        for (let col = 0; col < 7; col++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.row = row;
            cell.dataset.col = col;
            cell.addEventListener('click', () => handleCellClick(row, col));
            board.appendChild(cell);
        }
    }
}

// Starts a new single-player game
function startSinglePlayerGame() {
    titleScreen.style.display = 'none';
    gameScreen.style.display = 'block';
    currentPlayer = 'X';
    gameBoard = Array(6).fill().map(() => Array(7).fill(''));
    gameOver = false;
    createBoard();
    updateGameInfo();
}

// Starts a new multiplayer game
function startMultiplayerGame() {
    titleScreen.style.display = 'none';
    gameScreen.style.display = 'block';
    currentPlayer = 'X';
    gameBoard = Array(6).fill().map(() => Array(7).fill(''));
    gameOver = false;
    createBoard();
    updateGameInfo();
}

// Handles a cell click
function handleCellClick(row, col) {
    if (gameOver || gameBoard[row][col] !== '') return;

    for (let i = 5; i >= 0; i--) {
        if (gameBoard[i][col] === '') {
            gameBoard[i][col] = currentPlayer;
            updateBoard();
            checkWinner(i, col);
            switchPlayer();
            break;
        }
    }
}

// Updates the game board display
function updateBoard() {
    const cells = document.querySelectorAll('.cell');
    cells.forEach(cell => {
        const row = cell.dataset.row;
        const col = cell.dataset.col;
        cell.classList.remove('X', 'O');
        if (gameBoard[row][col] === 'X') {
            cell.classList.add('X');
        } else if (gameBoard[row][col] === 'O') {
            cell.classList.add('O');
        }
    });
}

// Switches the current player
function switchPlayer() {
    currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
    updateGameInfo();
}

// Updates the current player display
function updateGameInfo() {
    currentPlayerDisplay.textContent = `Player ${currentPlayer === 'X' ? '1 (X)' : '2 (O)'}`;
}

// Checks if the current move results in a win
function checkWinner(row, col) {
    if (checkDirection(row, col, -1, 0) + checkDirection(row, col, 1, 0) >= 3 || // Vertical
        checkDirection(row, col, 0, -1) + checkDirection(row, col, 0, 1) >= 3 || // Horizontal
        checkDirection(row, col, -1, -1) + checkDirection(row, col, 1, 1) >= 3 || // Diagonal \
        checkDirection(row, col, -1, 1) + checkDirection(row, col, 1, -1) >= 3) { // Diagonal /
        
        gameOver = true;
        status.textContent = `Player ${currentPlayer === 'X' ? '1 (X)' : '2 (O)'} Wins!`;
        retryButton.style.display = 'inline-block';
        goToTitleButton.style.display = 'inline-block';
    } else if (gameBoard.flat().every(cell => cell !== '')) {
        gameOver = true;
        status.textContent = 'It\'s a Draw!';
        retryButton.style.display = 'inline-block';
        goToTitleButton.style.display = 'inline-block';
    }
}

// Checks a specific direction (vertical, horizontal, or diagonal)
function checkDirection(row, col, dRow, dCol) {
    let count = 0;
    let r = row + dRow;
    let c = col + dCol;
    while (r >= 0 && r < 6 && c >= 0 && c < 7 && gameBoard[r][c] === currentPlayer) {
        count++;
        r += dRow;
        c += dCol;
    }
    return count;
}

// Restarts the game
function restartGame() {
    gameBoard = Array(6).fill().map(() => Array(7).fill(''));
    gameOver = false;
    retryButton.style.display = 'none';
    goToTitleButton.style.display = 'none';
    createBoard();
    updateGameInfo();
    status.textContent = '';
}

// Returns to the title screen
function goToTitleScreen() {
    gameScreen.style.display = 'none';
    titleScreen.style.display = 'block';
}
