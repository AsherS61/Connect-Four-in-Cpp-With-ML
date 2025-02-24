let board;
let currentPlayer;
let gameMode;
let gameOver = false;

function startGame(mode) {
  gameMode = mode;
  currentPlayer = 'x'; // Player 1 starts (red)
  board = Array(6).fill().map(() => Array(7).fill(null)); // 6x7 board
  gameOver = false;
  
  document.getElementById('mode-selection').style.display = 'none';
  document.getElementById('game-board').style.display = 'block';
  
  renderBoard();
  updateTurnStatus();
}

function renderBoard() {
  const boardContainer = document.querySelector('.board');
  boardContainer.innerHTML = '';
  
  for (let row = 0; row < 6; row++) {
    for (let col = 0; col < 7; col++) {
      const cell = document.createElement('div');
      cell.classList.add('cell');
      if (board[row][col]) {
        cell.classList.add(board[row][col]); // Add x or o class
      }
      cell.onclick = () => handleMove(col);
      boardContainer.appendChild(cell);
    }
  }
}

function handleMove(col) {
  if (gameOver) return;

  // Find the first empty spot in the column
  for (let row = 5; row >= 0; row--) {
    if (!board[row][col]) {
      board[row][col] = currentPlayer;
      checkWinner(row, col);
      currentPlayer = currentPlayer === 'x' ? 'o' : 'x'; // Switch player
      break;
    }
  }

  if (gameMode === 'single' && currentPlayer === 'o' && !gameOver) {
    aiMove();
  }

  renderBoard();
  updateTurnStatus();
}

function checkWinner(row, col) {
  if (checkDirection(row, col, 1, 0) || // Horizontal
      checkDirection(row, col, 0, 1) || // Vertical
      checkDirection(row, col, 1, 1) || // Diagonal \
      checkDirection(row, col, 1, -1)) { // Diagonal /
    gameOver = true;
    setTimeout(() => alert(`${currentPlayer === 'x' ? 'Player 1' : 'AI'} wins!`), 100);
  }
}

function checkDirection(row, col, rowDir, colDir) {
  let count = 1;
  
  for (let i = 1; i < 4; i++) {
    const r = row + rowDir * i;
    const c = col + colDir * i;
    if (r < 0 || r >= 6 || c < 0 || c >= 7 || board[r][c] !== currentPlayer) break;
    count++;
  }
  
  for (let i = 1; i < 4; i++) {
    const r = row - rowDir * i;
    const c = col - colDir * i;
    if (r < 0 || r >= 6 || c < 0 || c >= 7 || board[r][c] !== currentPlayer) break;
    count++;
  }

  return count >= 4;
}

function aiMove() {
  if (gameOver) return;
  
  // AI logic to make a move (simple random move)
  for (let col = 0; col < 7; col++) {
    for (let row = 5; row >= 0; row--) {
      if (!board[row][col]) {
        board[row][col] = 'o';
        checkWinner(row, col);
        currentPlayer = 'x'; // Switch back to player
        return;
      }
    }
  }
}

function updateTurnStatus() {
  const turnText = gameMode === 'single' ? 
    `Turn: ${currentPlayer === 'x' ? 'Player 1' : 'AI'}` :
    `Player ${currentPlayer === 'x' ? '1' : '2'}'s Turn`;
  document.getElementById('turn-status').innerText = turnText;
}

function restartGame() {
  startGame(gameMode);
}
