function printf(varargin)
%PRINTF  An improved print command with status and timing functionality.
%
%   PRINTF works as a replacement for Matlab's FPRINTF. It is particularly
%   designed to easily print log messages of running processes. In addition
%   to formatted output it supports hierarchical grouping of more complex
%   command sequences, automatically printing a statuses as percentage
%   value as well as automatically printing the run time of single
%   processes and groups. PRINTF nicely works with Matlab's diary
%   functionality. Further you can adjust parameters to control
%   indentation, maximum depth of hierarchical output and line with.
%
%   PRINTF(S) is equivalent to using the built-in DISP command.
%
%   Example
%      printf('Hello World');
%
%   PRINTF(FORMAT,ARGS,...) is equivalent to using the built-in FPRINTF
%   function. Additional arguments ARGS are included in the output as
%   defined by the FORMAT string. (A newline character \n is added
%   automatically!)
%
%   Example
%      printf('%d + %d = %d', 1, 1, 1 + 1);
%
%   Calling PRINTF with a string ending with three dots '...' will start
%   timing the following commands. Only calling PRINTF without any
%   arguments will stop the time and print the elapsed time.
%
%   Example
%      N = 1000;
%      printf('Inverting a %dx%d matrix...', N, N);
%      inv(rand(N));
%      printf;
%
%   Very long lines are trimmed in order to have uniformly sized lines.
%
%   Example
%      printf(['This is a very very long line ' ...
%          'with lots of information about the ongoing computations']);
%      printf(['This line introduces an action that is timed: ' ...
%          'We should leave enough space for the number of seconds...']);
%      pause(0.1);
%      printf;
%
%   Actions are displayed hierarchically if multiple titles follow each
%   other without printing times in between.
%
%   Example
%      printf('A timed group of actions...');
%      for i = 1 : 3
%          printf('Action %d...', i);
%          pause(0.1);
%          printf;
%      end
%      for i = 4 : 6
%          printf('Action %d (no time)', i);
%          pause(0.1);
%      end
%      printf;
%
%   PRINTF(STATUS) prints the current STATUS (a scalar from 0 to 1) as
%   percentage. This number later is overwritten with the elapsed time.
%
%   Example
%      N = 900;
%      printf('Inverting %d matrices (%dx fprintf)...', N, N);
%      for n = 1 : N
%          inv(rand(100));
%          printf(n / N);
%      end
%      printf;
%
%   PRINTF(ITERATION,TOTAL) prints the status (computed from two scalars:
%   status = ITERATION / TOTAL) as percentage. In contrast to passing one
%   argument STATUS only, this two-argument alternative will print a number
%   only if the integer percentage changed since the last call which can
%   reduce the number of prints to the command line significantly. This
%   check is not possible with one argument only.
%
%   Example
%      printf('Inverting %d matrices (100x fprintf)...', N);
%      for n = 1 : N
%          inv(rand(100));
%          printf(n, N);
%      end
%      printf;
%
%   PRINTF('!set',PARAMETER,VALUE,...) enables to change internal PRINTF
%   settings. Possible parameters are line width 'width', indentation
%   'indent' and maximum 'depth' of the hierarchical output.
%
%   Example
%      printf('!set', 'width', 60, 'indent', 2, 'depth', 2);
%
%   PRINTF('!reset') will restore all default settings.
%
%   PRINTF('!clear') will clear the print stack. (When developing a piece
%   of software, you might have stopped the program during one action. Now
%   the concluding PRINTF command is missing and all following output will
%   be printed with additional indentation. The PRINTF function can not
%   determine whether there is still a complicated action is going on or if
%   the program stopped completely.)
%
%   Example
%      printf('Some action with timing that is interrupted...');
%      printf('Output with too much indentation');
%      printf('!clear');
%      printf('Output with correct indentation');
%
%   See also DISP, FPRINTF, TIC, TOC, DIARY
%
%   Copyright 2012 Falko Schindler
%   $Revision: 1.01 $  $Date: 2012/10/23 16:26:00 $

%% settings, print stack and line feed
persistent PRINTF;
defaultSettings = struct('width', 75, 'indent', 4, 'depth', inf);
if isempty(PRINTF)
    PRINTF = defaultSettings;
    PRINTF.stack = [];
    PRINTF.feed = 0;
end

%% change some setting
if nargin >= 3 && strcmp(varargin{1}, '!set')
    for i = 2 : 2 : nargin - 1
    	PRINTF.(lower(varargin{i})) = varargin{i + 1};
    end
    return
end

%% clear print stack and feed
if nargin == 1 && strcmp(varargin{1}, '!reset')
    for n = fieldnames(defaultSettings)'
        PRINTF.(n{1}) = defaultSettings.(n{1});
    end
    return
end

%% clear print stack and feed
if nargin == 1 && strcmp(varargin{1}, '!clear')
    if PRINTF.feed
        fprintf('\n');
    end
    PRINTF.stack = [];
    PRINTF.feed = 0;
    return
end

%% detect diary status
diaryStatus = get(0, 'Diary');

%% parse title
if nargin && ischar(varargin{1})
    string = sprintf(varargin{1}, varargin{2 : end});
    right = 0;
    PRINTF.stack(end + 1) = now;
    ongoing = numel(string) > 3 && strcmp(string(end - 2 : end), '...');
    if ongoing
        string(end - 2 : end) = [];
    end
    maxSize = PRINTF.width - ...
        (numel(PRINTF.stack) - 1) * PRINTF.indent - 12 * ongoing;
    if numel(string) > maxSize
        string = strtrim(string(1 : maxSize - 3));
        string(end + 1 : maxSize) = '.';
    else
        string(end + 1) = ' ';
    end
    if ~ongoing
        string(end + 1) = 10;
    end
end

%% parse status
if nargin && isscalar(varargin{1})
    if nargin == 2 && isscalar(varargin{2})
        if ~any(varargin{1} == round((1 : 100) * varargin{2} / 100))
            return
        end
        string = sprintf(' %.0f %%', varargin{1} / varargin{2} * 100);
	else
        string = sprintf(' %.0f %%', varargin{1} * 100);
    end
    right = 1;
    diary off;
end

%% parse time
if ~nargin && ~isempty(PRINTF.stack)
    string = sprintf('%.3f sec\n', sum(datevec(now - PRINTF.stack(end))));
    if PRINTF.feed > 0
        string = [' ', string];
    end
    right = PRINTF.feed > 0;
end

%% print string
if numel(PRINTF.stack) <= PRINTF.depth && exist('string', 'var')
    if right
        target = PRINTF.width - numel(string) + (string(end) == 10);
        dots = target - PRINTF.feed;
        back = PRINTF.feed - target;
        if strcmp(diaryStatus, 'on') && ...
           strcmp(get(0, 'Diary'), 'on') && back
            extra = target - PRINTF.diaryFeed;
            fprintf(repmat('.', 1, extra));
            diary off;
            fprintf(repmat('\b', 1, extra + back));
            diary on;
            fprintf('%s', string);
        else
            fprintf([ ...
                repmat('.', 1, dots), ...
                repmat('\b', 1, back), '%s'], string);
        end
    else
        if PRINTF.feed > 0 && PRINTF.feed < PRINTF.width
            fprintf('\n');
            PRINTF.feed = 0;
        end
        target = PRINTF.indent * (numel(PRINTF.stack) - 1);
        fprintf([ ...
            repmat(' ', 1, target - PRINTF.feed), ...
            '%s'], string);
    end
    PRINTF.feed = (target + numel(string)) * (string(end) ~= 10);
    if strcmp(get(0, 'Diary'), 'on')
        PRINTF.diaryFeed = PRINTF.feed;
    end
end

%% remove last element from print stack if '\n' printed
if exist('string', 'var') && string(end) == 10
    PRINTF.stack(end) = [];
end

%% restore diary status
diary(diaryStatus);
